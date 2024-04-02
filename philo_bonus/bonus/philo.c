/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:35:38 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/02 14:55:02 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static int	sleeping(t_philo *philo)
{
	print_lock(philo, "is sleeping");
	usleep(philo->meta->t_sleep * 1000);
	return (EXIT_SUCCESS);
}

static int	grab_forks(t_philo *philo)
{
	sem_wait(philo->meta->forks);
	print_lock(philo, "has taken a fork");
	sem_wait(philo->meta->forks);
	print_lock(philo, "has taken a fork");
	return (1);
}

static int	eat(t_philo *philo)
{
	if (grab_forks(philo))
	{
		philo->last_ate = get_time(philo->meta, 0);
		print_lock(philo, "is eating");
		philo->times_ate += 1;
		usleep(philo->meta->t_eat * 1000);
		sem_post(philo->meta->forks);
		sem_post(philo->meta->forks);
	}
	return (EXIT_SUCCESS);
}

void	run_philo(t_philo *philo)
{
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			sleeping(philo);
			print_lock(philo, "is thinking");
			eat(philo);
		}
		else
		{
			eat(philo);
			sleeping(philo);
			print_lock(philo, "is thinking");
		}
	}
}
