/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:57:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/22 13:17:45 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

extern t_meta meta;
int	sigint = 0;

void	kill_children(t_meta *meta)
{
	int	i;

	i = 0;
	while (i <meta->n_philos)
	{
		kill(meta->philos[i].pid, SIGKILL);
		i++;
	}
	return ;
}

void sigint_handler()
{
	sigint = 1;
	exit(EXIT_FAILURE);
}

void	start_simulation(t_meta *meta)
{
	int	i;

	signal(SIGINT, sigint_handler);
	i = 0;
	while (i < meta->n_philos)
	{
		child_process(&meta->philos[i]);
		i++;
	}
	i = 0;
	while (i < meta->n_philos)
		waitpid(meta->philos[i++].pid, NULL, 0);
	while (!sigint)
		sleep(1);
	// kill_children(meta);
}
