/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:54:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/12 16:08:18 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_forks(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_mutex_init(&meta->forks[i], NULL) != 0)
			exit_error(ERR_MUTEX, NULL, 3, meta);
		i++;
	}
}

void	init_philos(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		meta->philos[i].state = 0;
		meta->philos[i].l_fork = i;
		meta->philos[i].r_fork = i % (meta->n_philos - 1);
		i++;
	}
}

int	init_meta(int argc, char **argv, t_meta *meta)
{

	meta->n_philos = ft_atoi(argv[1]);
	meta->t_die = ft_atoi(argv[2]);
	meta->t_eat = ft_atoi(argv[3]);
	meta->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		meta->n_must_eat = ft_atoi(argv[5]);
	else
		meta->n_must_eat = 0;
	meta->philos = ft_calloc((meta->n_philos + 1), sizeof(t_philo));
	meta->forks = ft_calloc((meta->n_philos + 1), sizeof(pthread_mutex_t));
	if (!meta->philos || !meta->forks)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	init_forks(meta);
	init_philos(meta);
	return (EXIT_SUCCESS);
}
