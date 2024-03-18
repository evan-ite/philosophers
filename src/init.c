/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:54:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/18 17:45:17 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_meta *meta)
{
	int	i;

	meta->fork_flag = (int *)ft_calloc(meta->n_philos + 1, sizeof(int));
	if (!meta->fork_flag)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_mutex_init(&meta->forks[i], NULL) != 0)
			return (exit_error(ERR_MUTEX, NULL, 3, meta));
		meta->fork_flag[i] = 1;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_philos(t_meta *meta)
{
	int	i;

	meta->philos_flag = (int *)ft_calloc(meta->n_philos + 1, sizeof(int));
	i = 0;
	while (i < meta->n_philos)
	{
		meta->philos[i].id = i;
		meta->philos[i].last_ate = get_time(meta, 0);
		meta->philos[i].times_ate = 0;
		meta->philos[i].l_fork[0] = i;
		meta->philos[i].r_fork[0] = (i +  1) % meta->n_philos;
		meta->philos[i].l_fork[1] = 1;
		meta->philos[i].r_fork[1] = 1;
		meta->philos[i].meta = meta;
		meta->philos_flag[i] = 1;
		i++;
	}
}

static int	check_values(t_meta *meta)
{
	if (meta->t_die < 60 || meta->t_eat < 60 || meta->t_sleep < 60|| !meta->n_must_eat)
		return (exit_error("Times must be grater than 60ms", NULL, 2, meta));
	if (meta->n_philos == 1)
		return (exit_error("One solo philo will always die...", NULL, 2, meta));
	return (EXIT_SUCCESS);
}

int	init_meta(int argc, char **argv, t_meta *meta)
{
	meta->print_flag = 0;
	meta->monitor_flag = 0;
	meta->n_philos = ft_atoi(argv[1]);
	meta->t_die = ft_atoi(argv[2]);
	meta->t_eat = ft_atoi(argv[3]);
	meta->t_sleep = ft_atoi(argv[4]);
	meta->start_time = get_time(meta, 1);
	meta->all_alive = 1;
	if (argc == 6)
		meta->n_must_eat = ft_atoi(argv[5]);
	else
		meta->n_must_eat = -1;
	meta->philos = ft_calloc((meta->n_philos + 1), sizeof(t_philo));
	meta->forks = ft_calloc((meta->n_philos + 1), sizeof(pthread_mutex_t));
	if (!meta->philos || !meta->forks)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	if (check_values(meta))
		return (EXIT_FAILURE);
	if (init_forks(meta))
		return (EXIT_FAILURE);
	init_philos(meta);
	if (pthread_mutex_init(&meta->print_mutex, NULL) != 0)
			return (exit_error(ERR_MUTEX, NULL, 3, meta));
	meta->print_flag = 1;
	return (EXIT_SUCCESS);
}
