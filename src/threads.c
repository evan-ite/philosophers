/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 11:36:55 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_philo(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (philo->meta->all_alive)
	{
		if (philo->id % 2 == 0)
		{
			sleeping(philo);
			think(philo);
			eat(philo);
		}
		else
		{
			eat(philo);
			sleeping(philo);
			think(philo);
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

int	run(t_meta *meta)
{
	int	i;

	if (pthread_create(&meta->monitor_id, NULL, monitor, meta) != 0)
		return (exit_error(ERR_THD, NULL, 3, meta));
	meta->monitor_flag = 1;
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_create(&meta->philos[i].thread_id, NULL, \
			start_philo, &meta->philos[i]) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		i++;
	}
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_join(meta->philos[i].thread_id, NULL) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		meta->philos_flag[i] = 0;
		i++;
	}
	if (pthread_join(meta->monitor_id, NULL) != 0)
		return (exit_error(ERR_THD, NULL, 3, meta));
	return (EXIT_SUCCESS);
}
