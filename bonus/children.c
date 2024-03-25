/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:32:23 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/25 13:48:37 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*monitor(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (check_alive(philo->meta))
	{
		if (check_death(philo) || check_all_ate(philo))
		{
			sem_wait(philo->meta->all_alive);
			kill(-2, SIGKILL);
			return (NULL);
		}
	}
	return (NULL);
}

void	child_process(t_philo *philo)
{
	philo->pid = fork();
	if (philo->pid < 0)
		exit_error(ERR_CHILD, NULL, 3, philo->meta);
	if (philo->pid == 0)
	{
		if (pthread_create(&philo->monitor_id, NULL, monitor, philo) != 0)
			exit_error(ERR_THD, NULL, 3, philo->meta);
		run_philo(philo);
		if (pthread_join(philo->monitor_id, NULL) != 0)
			exit_error(ERR_THD, NULL, 3, philo->meta);
		exit(EXIT_SUCCESS);
	}
}
