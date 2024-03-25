/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:26:17 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/25 17:08:51 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	kill_children(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		kill(meta->philos[i].pid, SIGKILL);
		i++;
	}
}

void	wait_semaphores(int argc, t_meta *meta)
{
	int	i;

	sem_wait(meta->stop);
	if (argc == 6)
	{
		i = 0;
		while (++i < meta->n_philos)
			sem_wait(meta->stop);
	}
}

int	main(int argc, char **argv)
{
	t_meta	*meta;

	meta = ft_calloc(1, sizeof(t_meta));
	if (!meta)
		exit_error(ERR_CHILD, NULL, -1, NULL);
	if (!check_input(argc, argv))
		exit_error(ERR_INPUT, NULL, 1, NULL);
	init_meta(argc, argv, meta);
	wait_semaphores(argc, meta);
	start_simulation(meta);
	wait_semaphores(argc, meta);
	kill_children(meta);
	free_meta(meta);
	return (EXIT_SUCCESS);
}
