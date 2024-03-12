/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/12 17:24:21 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time()
{
	struct timeval	time;
	long long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_usec / 1000;
	return (time_ms);
}

int	sleeping(t_philo *philo)
{
	printf("%lld %i is sleeping\n", get_time(), philo->id);
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
		if (!philo->r_fork[1] && !philo->l_fork[1])
		{
			printf("%lld %i is eating\n", get_time(), philo->id);
			usleep(philo->meta->t_eat * 1000);
			pthread_mutex_unlock(&philo->meta->forks[philo->l_fork[0]]);
			philo->l_fork[1] = 1;
			pthread_mutex_unlock(&philo->meta->forks[philo->r_fork[0]]);
			philo->r_fork[1] = 1;
			break ;
		}
		else
			printf("%lld %i is thinking\n", get_time(), philo->id);
	}
	return (EXIT_SUCCESS);
}

int	think(t_philo *philo)
{
	printf("%lld %i is thinking\n", get_time(), philo->id);
	return (EXIT_SUCCESS);
}

void	*start_philo(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (philo->meta->all_alive)
	{
		sleeping(philo);
		// think(philo);
		eat(philo);
	}
	return (philo);
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
