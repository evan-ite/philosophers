/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:35:38 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/25 13:48:04 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	sem_post(philo->meta->forks);
	sem_post(philo->meta->forks);
	return (1);
}

static int	eat(t_philo *philo)
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

int	check_alive(t_meta *meta)
{
	sem_wait(meta->all_alive);
	sem_post(meta->all_alive);
	return (1);
}

void	run_philo(t_philo *philo)
{
	while (check_alive(philo->meta))
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
