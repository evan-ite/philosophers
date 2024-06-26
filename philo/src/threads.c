/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/05 11:50:40 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_alive(t_meta *meta)
{
	pthread_mutex_lock(&meta->alive);
	if (meta->all_alive == 1)
	{
		pthread_mutex_unlock(&meta->alive);
		return (1);
	}
	pthread_mutex_unlock(&meta->alive);
	return (0);
}

static void	*start_philo(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (check_alive(philo->meta))
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

static void	*monitor(void *void_meta)
{
	t_meta	*meta;
	int		i;

	meta = (t_meta *)void_meta;
	i = 0;
	while (check_alive(meta))
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
		usleep(1);
		i++;
	}
	if (pthread_join(meta->monitor_id, NULL) != 0)
		return (exit_error(ERR_THD, NULL, 3, meta));
	meta->monitor_flag = 0;
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_join(meta->philos[i].thread_id, NULL) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		meta->philos_flag[i++] = 0;
	}
	return (EXIT_SUCCESS);
}
