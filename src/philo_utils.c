/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:51:46 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/18 14:44:25 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sleeping(t_philo *philo)
{
	print_lock(philo, "is sleeping");
	usleep(philo->meta->t_sleep * 1000);
	return (EXIT_SUCCESS);
}

static int	grab_forks(t_philo *philo)
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
		print_lock(philo, "has taken a fork");
		print_lock(philo, "has taken a fork");
		return (1);
	}
	else
		return (0);
}

int	eat(t_philo *philo)
{
	while (1)
	{
		if (grab_forks(philo))
		{
			philo->last_ate = get_time(philo->meta, 0);
			print_lock(philo, "is eating");
			philo->times_ate+= 1;
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
	print_lock(philo, "is thinking");
	return (EXIT_SUCCESS);
}
