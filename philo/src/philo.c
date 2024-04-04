/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:51:46 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/04 18:20:09 by evan-ite         ###   ########.fr       */
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
	if (philo->id % 2 == 0)
	{
		if (philo->times_ate == 0)
			usleep(1000);
		pthread_mutex_lock(&philo->meta->forks[philo->r_fork]);
		print_lock(philo, "has taken a fork");
		pthread_mutex_lock(&philo->meta->forks[philo->l_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->meta->forks[philo->l_fork]);
		print_lock(philo, "has taken a fork");
		pthread_mutex_lock(&philo->meta->forks[philo->r_fork]);
	}
	print_lock(philo, "has taken a fork");
	return (1);
}

int	eat(t_philo *philo)
{
	while (check_alive(philo->meta))
	{
		if (philo->meta->n_philos == 1)
			break ;
		if (philo->id == 1 && (philo->meta->n_philos % 2) != 0 \
			&& philo->times_ate == 0)
			usleep(philo->meta->t_eat * 1000);
		if (grab_forks(philo))
		{
			philo->last_ate = get_time(philo->meta, 0);
			print_lock(philo, "is eating");
			philo->times_ate += 1;
			usleep(philo->meta->t_eat * 1000);
			pthread_mutex_unlock(&philo->meta->forks[philo->l_fork]);
			pthread_mutex_unlock(&philo->meta->forks[philo->r_fork]);
			break ;
		}
	}
	return (EXIT_SUCCESS);
}

int	think(t_philo *philo)
{
	print_lock(philo, "is thinking");
	if (!(philo->meta->n_philos % 2))
		usleep(10);
	else
	{
		if ((philo->meta->t_die - philo->meta->t_eat \
			- philo->meta->t_sleep) <= 0)
			usleep(900);
		else
			usleep((philo->meta->t_die - philo->meta->t_eat \
			- philo->meta->t_sleep) * 900);
	}
	return (EXIT_SUCCESS);
}
