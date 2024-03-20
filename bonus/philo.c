/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:35:38 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 11:39:05 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	run_philo(t_philo *philo)
{
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
}
