/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/13 14:39:49 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sleeping(t_philo *philo)
{
	print_lock(philo, "sleeping");
	usleep(philo->meta->t_sleep * 1000);
	return (EXIT_SUCCESS);
}

int	eat(t_philo *philo)
{
	while (1)
	{
		if (philo->l_fork[1])
		{
			pthread_mutex_lock(&philo->meta->forks[philo->l_fork[0]]);
			philo->l_fork[1] = 0;
		}
		if (!philo->l_fork[1] && philo->r_fork[1])
		{
			pthread_mutex_lock(&philo->meta->forks[philo->r_fork[0]]);
			philo->r_fork[1] = 0;
		}
		else
		{
			pthread_mutex_unlock(&philo->meta->forks[philo->l_fork[0]]);
			philo->l_fork[1] = 1;
		}
		if (!philo->r_fork[1] && !philo->l_fork[1])
		{
			print_lock(philo, "eating");
			usleep(philo->meta->t_eat * 1000);
			pthread_mutex_unlock(&philo->meta->forks[philo->l_fork[0]]);
			philo->l_fork[1] = 1;
			pthread_mutex_unlock(&philo->meta->forks[philo->r_fork[0]]);
			philo->r_fork[1] = 1;
			philo->last_ate = get_time(philo->meta, 0);
			break ;
		}
	}
	return (EXIT_SUCCESS);
}

int	think(t_philo *philo)
{
	print_lock(philo, "thinking");
	return (EXIT_SUCCESS);
}

void	*start_philo(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (philo->meta->all_alive)
	{
		sleeping(philo);
		think(philo);
		eat(philo);
	}
	return (NULL);
}

void	*monitor(void *void_meta)
{
	t_meta	*meta;
	int		i;

	meta = (t_meta *)void_meta;
	i = 0;
	while (i < meta->n_philos)
	{
		if ((get_time(meta, 0) - meta->philos[i].last_ate) >= meta->t_die)
		{
			meta->all_alive = 0;
			print_lock(&meta->philos[i], "dead");
			break ;
		}
	}
	return (NULL);
}

int	run(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_create(&meta->philos[i].thread_id, NULL, start_philo, &meta->philos[i]) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		i++;
	}
	if (pthread_create(&meta->monitor_id, NULL, monitor, &meta) != 0)
		return (exit_error(ERR_THD, NULL, 3, meta));
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_join(meta->philos[i].thread_id, NULL) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		i++;
	}
	printf("finished all threads \n");
	return (EXIT_SUCCESS);
}
