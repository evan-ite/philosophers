/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:57:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 11:37:41 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	child_process(t_philo *philo)
{
	philo->pid = fork();
	if (philo->pid < 0)
		exit_error(ERR_CHILD, NULL, 3, philo->meta);
	if (philo->pid == 0)
		run_philo(philo);
}

void	*monitor(void *void_meta)
{
	t_meta	*meta;
	int		i;

	meta = (t_meta *)void_meta;
	i = 0;
	while (meta->all_alive)
	{
		if (check_death(&meta->philos[i]))
			return (NULL);
		else if (check_all_ate(meta))
			return (NULL);
		i++;
		i = i % meta->n_philos;
	}
	return (NULL);
}

void	start_simulation(t_meta *meta)
{
	int	i;

	if (pthread_create(&meta->monitor_id, NULL, monitor, meta) != 0)
		return (exit_error(ERR_THD, NULL, 3, meta));
	meta->monitor_flag = 1;
	i = 0;
	while (i < meta->n_philos)
	{
		child_process(&meta->philos[i]);
		i++;
	}
	if (pthread_join(meta->monitor_id, NULL) != 0)
		exit_error(ERR_THD, NULL, 3, meta);
}
