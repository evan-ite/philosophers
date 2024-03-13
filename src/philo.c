/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/13 18:01:52 by evan-ite         ###   ########.fr       */
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
			philo->r_fork[1] = 1;
			philo->l_fork[1] = 1;
			philo->last_ate = get_time(philo->meta, 0);
			pthread_mutex_unlock(&philo->meta->forks[philo->l_fork[0]]);
			pthread_mutex_unlock(&philo->meta->forks[philo->r_fork[0]]);
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

int	check_death(t_philo *philo)
{
	if ((get_time(philo->meta, 0) - philo->last_ate) >= philo->meta->t_die)
	{
		philo->meta->all_alive = 0;
		print_lock(philo, "dead");
		return (1);
	}
	return (0);
}

void	*start_philo(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (philo->meta->all_alive)
	{
		if (philo->id % 2 == 0)
		{
			sleeping(philo);
			if (check_death(philo))
				break;
			think(philo);
			if (check_death(philo))
				break;
			eat(philo);
		}
		else
		{
			eat(philo);
			sleeping(philo);
			if (check_death(philo))
				break;
			think(philo);
			if (check_death(philo))
				break;
		}
	}
	return (NULL);
}

void	*monitor(void *void_meta)
{
	t_meta	*meta;
	int		i;

	meta = (t_meta *)void_meta;
	i = 0;
	while (meta->all_alive == 1)
	{
		// printf("TEST %i\n", i);
		if ((get_time(meta, 0) - meta->philos[i].last_ate) >= meta->t_die)
		{
			meta->all_alive = 0;
			print_lock(&meta->philos[i], "dead");
		}
		i++;
		i = i % meta->n_philos;
	}
	return (NULL);
}

int	run(t_meta *meta)
{
	int	i;

	// if (pthread_create(&meta->monitor_id, NULL, monitor, meta) != 0)
	// 	return (exit_error(ERR_THD, NULL, 3, meta));
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_create(&meta->philos[i].thread_id, NULL, start_philo, &meta->philos[i]) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		i++;
	}
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
