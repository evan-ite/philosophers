/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:55:29 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/05 13:05:41 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	init_philos(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		meta->philos[i].id = i + 1;
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
		meta->t_sleep < 60)
		return (exit_error("Times must be greater than 60ms", NULL, 2, meta));
	if (!meta->n_must_eat)
		return (exit_error("Time to eat must be greater than 0", \
		NULL, 2, meta));
	return (EXIT_SUCCESS);
}

static void	init_sems(int argc, char **argv, t_meta *meta)
{
	sem_unlink("/stop");
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	if (argc == 6)
	{
		meta->n_must_eat = ft_atoi(argv[5]);
		meta->stop = sem_open("/stop", O_CREAT, 0666, meta->n_philos);
	}
	else
	{
		meta->n_must_eat = -1;
		meta->stop = sem_open("/stop", O_CREAT, 0666, 1);
	}
	if (meta->stop == SEM_FAILED)
		exit_error(ERR_SEM, NULL, -1, meta);
	meta->forks = sem_open("/forks", O_CREAT, 0666, meta->n_philos);
	if (meta->forks == SEM_FAILED)
		exit_error(ERR_SEM, NULL, -1, meta);
	meta->print = sem_open("/print", O_CREAT, 0666, 1);
	if (meta->print == SEM_FAILED)
		exit_error(ERR_SEM, NULL, -1, meta);
	meta->death = sem_open("/death", O_CREAT, 0666, 1);
	if (meta->death == SEM_FAILED)
		exit_error(ERR_SEM, NULL, -1, meta);
}

int	init_meta(int argc, char **argv, t_meta *meta)
{
	meta->n_philos = ft_atoi(argv[1]);
	meta->t_die = ft_atoi(argv[2]);
	meta->t_eat = ft_atoi(argv[3]);
	meta->t_sleep = ft_atoi(argv[4]);
	meta->start_time = get_time(meta, 1);
	meta->philos = ft_calloc((meta->n_philos + 1), sizeof(t_philo));
	if (!meta->philos)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	init_sems(argc, argv, meta);
	check_values(meta);
	init_philos(meta);
	return (EXIT_SUCCESS);
}
