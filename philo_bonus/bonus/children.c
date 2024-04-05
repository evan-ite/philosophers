/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:32:23 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/05 14:44:49 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	post_semaphores(t_meta *meta)
{
	int	i;

	i = 0;
	while (i++ < meta->n_philos)
		sem_post(meta->stop);
}

static void	*monitor(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		sem_wait(philo->meta->death);
		if (check_death(philo))
		{
			sem_post(philo->meta->stop);
			sem_post(philo->meta->death);
			if (philo->meta->n_must_eat > 0)
				post_semaphores(philo->meta);
			break ;
		}
		else if (check_times_ate(philo))
		{
			sem_post(philo->meta->stop);
			sem_post(philo->meta->death);
			break ;
		}
		sem_post(philo->meta->death);
	}
	return (NULL);
}

static void	child_process(t_philo *philo)
{
	philo->pid = fork();
	if (philo->pid < 0)
		exit_error(ERR_CHILD, NULL, 3, philo->meta);
	if (philo->pid == 0)
	{
		if (pthread_create(&philo->monitor_id, NULL, monitor, philo) != 0)
			exit_error(ERR_THD, NULL, 3, philo->meta);
		pthread_detach(philo->monitor_id);
		run_philo(philo);
		exit(EXIT_SUCCESS);
	}
}

void	start_simulation(t_meta *meta)
{
	int		i;

	i = 0;
	while (i < meta->n_philos)
	{
		child_process(&meta->philos[i]);
		usleep(1);
		i++;
	}
}
