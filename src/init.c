/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:54:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/13 12:56:23 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_mutex_init(&meta->forks[i], NULL) != 0)
			return (exit_error(ERR_MUTEX, NULL, 3, meta));
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_philos(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		meta->philos[i].id = i;
		meta->philos[i].last_ate = get_time(meta);
		meta->philos[i].l_fork[0] = i;
		meta->philos[i].r_fork[0] = (i +  1) % meta->n_philos;
		meta->philos[i].l_fork[1] = 1;
		meta->philos[i].r_fork[1] = 1;
		meta->philos[i].meta = meta;
		i++;
	}
}

int	init_meta(int argc, char **argv, t_meta *meta)
{

	meta->n_philos = ft_atoi(argv[1]);
	meta->t_die = ft_atoi(argv[2]);
	meta->t_eat = ft_atoi(argv[3]);
	meta->t_sleep = ft_atoi(argv[4]);
	meta->all_alive = 1;
	if (argc == 6)
		meta->n_must_eat = ft_atoi(argv[5]);
	else
		meta->n_must_eat = 0;
	meta->philos = ft_calloc((meta->n_philos + 1), sizeof(t_philo));
	meta->forks = ft_calloc((meta->n_philos + 1), sizeof(pthread_mutex_t));
	if (!meta->philos || !meta->forks)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	if (init_forks(meta))
		return (EXIT_FAILURE);
	init_philos(meta);
	// if (pthread_mutex_init(&meta->time_mutex, NULL) != 0)
	// 		return (exit_error(ERR_MUTEX, NULL, 3, meta));
	// if (pthread_mutex_init(&meta->print_mutex, NULL) != 0)
	// 		return (exit_error(ERR_MUTEX, NULL, 3, meta));
	return (EXIT_SUCCESS);
}
