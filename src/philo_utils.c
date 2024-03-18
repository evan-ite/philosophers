/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:51:46 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/18 12:55:23 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sleeping(t_philo *philo)
{
	print_lock(philo, "sleeping");
	usleep(philo->meta->t_sleep * 1000);
	return (EXIT_SUCCESS);
}

int	eat(t_philo *philo)
{
	while (1)
	{
		if (philo->l_fork[1])
		{
			pthread_mutex_lock(&philo->meta->forks[philo->l_fork[0]]);
			philo->l_fork[1] = 0;
		}
		if (!philo->l_fork[1] && philo->r_fork[1])
		{
			pthread_mutex_lock(&philo->meta->forks[philo->r_fork[0]]);
			philo->r_fork[1] = 0;
		}
		else
		{
			pthread_mutex_unlock(&philo->meta->forks[philo->l_fork[0]]);
			philo->l_fork[1] = 1;
		}
		if (!philo->r_fork[1] && !philo->l_fork[1])
		{
			philo->last_ate = get_time(philo->meta, 0);
			print_lock(philo, "eating");
			usleep(philo->meta->t_eat * 1000);
			philo->r_fork[1] = 1;
			philo->l_fork[1] = 1;
			pthread_mutex_unlock(&philo->meta->forks[philo->l_fork[0]]);
			pthread_mutex_unlock(&philo->meta->forks[philo->r_fork[0]]);
			break ;
		}
	}
	return (EXIT_SUCCESS);
}

int	think(t_philo *philo)
{
	print_lock(philo, "thinking");
	return (EXIT_SUCCESS);
}

int	check_death(t_philo *philo)
{
	if ((get_time(philo->meta, 0) - philo->last_ate) >= philo->meta->t_die)
	{
		print_lock(philo, "dead");
		philo->meta->all_alive = 0;
		return (1);
	}
	return (0);
}
