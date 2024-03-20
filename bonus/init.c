/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:55:29 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 15:20:13 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	init_philos(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		meta->philos[i].id = i;
		meta->philos[i].last_ate = get_time(meta, 0);
		meta->philos[i].times_ate = 0;
		meta->philos[i].meta = meta;
		meta->philos[i].monitor_flag = 0;
		i++;
	}
}

static int	check_values(t_meta *meta)
{
	if (meta->t_die < 60 || meta->t_eat < 60 || \
		meta->t_sleep < 60 || !meta->n_must_eat)
		return (exit_error("Times must be grater than 60ms", NULL, 2, meta));
	if (meta->n_philos == 1)
	{
		printf("%lld %i %s\n", get_time(meta, 0), 1, "is dead");
		return (exit_error(NULL, NULL, 2, meta));
	}
	return (EXIT_SUCCESS);
}

int	init_meta(int argc, char **argv, t_meta *meta)
{
	meta->print_flag = 0;
	meta->fork_flag = 0;
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
	if (!meta->philos)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	check_values(meta);
	if (sem_init(&meta->forks, 1, meta->n_philos) != 0)
		exit_error(ERR_SEM, NULL, 2, meta);
	meta->fork_flag = 1;
	init_philos(meta);
	if (sem_init(&meta->print, 1, 1) != 0)
		exit_error(ERR_SEM, NULL, 3, meta);
	meta->print_flag = 1;
	return (EXIT_SUCCESS);
}

