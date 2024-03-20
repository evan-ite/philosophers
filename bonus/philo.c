/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:35:38 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 15:48:17 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	sleeping(t_philo *philo)
{
	print_lock(philo, "is sleeping");
	usleep(philo->meta->t_sleep * 1000);
	return (EXIT_SUCCESS);
}

static int	think(t_philo *philo)
{
	print_lock(philo, "is thinking");
	return (EXIT_SUCCESS);
}

static int	grab_forks(t_philo *philo)
{
	sem_wait(&philo->meta->forks);
	print_lock(philo, "has taken a fork");
	sem_wait(&philo->meta->forks);
	print_lock(philo, "has taken a fork");
	sem_post(&philo->meta->forks);
	sem_post(&philo->meta->forks);
	return (1);
}

int	eat(t_philo *philo)
{
	if (grab_forks(philo))
	{
		philo->last_ate = get_time(philo->meta, 0);
		// printf("philo %i UPDATE LAST ATE %lld\n", philo->id + 1, philo->last_ate);
		print_lock(philo, "is eating");
		philo->times_ate += 1;
		// printf("philo %i UPDATE TIMES ATE %i \n", philo->id + 1, philo->times_ate);
		usleep(philo->meta->t_eat * 1000);
	}
	return (EXIT_SUCCESS);
}

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
