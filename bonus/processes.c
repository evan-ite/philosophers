/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:57:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 15:47:16 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	sigterm_handler()
{
	printf("EXITING\n");
	exit (EXIT_SUCCESS);
}

void	kill_children(t_meta *meta)
{
	int	i;

	i = 0;
	while (i <meta->n_philos)
		kill(meta->philos[i++].pid, SIGTERM);
}

void	*monitor(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (philo->meta->all_alive)
	{
		if (check_death(philo) || check_all_ate(philo))
		{
			kill_children(philo->meta);
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
		signal(SIGTERM, sigterm_handler);
		if (pthread_create(&philo->monitor_id, NULL, monitor, philo) != 0)
			exit_error(ERR_THD, NULL, 3, philo->meta);
		philo->monitor_flag = 1;
		run_philo(philo);
		if (pthread_join(philo->monitor_id, NULL) != 0)
			exit_error(ERR_THD, NULL, 3, philo->meta);
		exit(EXIT_SUCCESS);
	}
}

void	start_simulation(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		child_process(&meta->philos[i]);
		i++;
	}

}
