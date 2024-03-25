/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:57:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/25 13:47:30 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	start_simulation(t_meta *meta)
{
	int	i;

	i = 0;
	// sem_wait()
	while (i < meta->n_philos)
	{
		child_process(&meta->philos[i]);
		i++;
	}
	i = 0;
	while (i < meta->n_philos)
		waitpid(meta->philos[i++].pid, NULL, 0);
}
