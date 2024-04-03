/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:51:46 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/03 15:32:37 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sleeping(t_philo *philo)
{
	print_lock(philo, "is sleeping");
	usleep(philo->meta->t_sleep * 1000);
	return (EXIT_SUCCESS);
}

static int	handle_fork(int fork, int to_state, t_philo *philo)
{
	pthread_mutex_lock(&philo->meta->forks[fork]);
	if (philo->meta->fork_flag[fork] == to_state)
	{
		pthread_mutex_unlock(&philo->meta->forks[fork]);
		return (0);
	}
	philo->meta->fork_flag[fork] = to_state;
	pthread_mutex_unlock(&philo->meta->forks[fork]);
	return (1);
}

// static int	check_ngrab(int fork1, int fork2, t_philo *philo)
// {
// 	int	f1;
// 	int	f2;

// 	f1  = handle_fork(fork1, GRAB, philo);
// 	f2 = handle_fork(fork2, GRAB, philo);
// 	if (f1 && f2)
// 	{
// 		print_lock(philo, "has taken a fork");
// 		print_lock(philo, "has taken a fork");
// 		return (1);
// 	}
// 	else if (f1)
// 		handle_fork(fork1, DROP, philo);
// 	else if (f2)
// 		handle_fork(fork2, DROP, philo);
// 	return (0);
// }

static int	grab_forks(t_philo *philo)
{
	int	f1;
	int	f2;

	f1  = handle_fork(philo->l_fork, GRAB, philo);
	f2 = handle_fork(philo->r_fork, GRAB, philo);
	if (f1 && f2)
	{
		print_lock(philo, "has taken a fork");
		print_lock(philo, "has taken a fork");
		return (1);
	}
	else if (f1)
		handle_fork(philo->l_fork, DROP, philo);
	else if (f2)
		handle_fork(philo->r_fork, DROP, philo);
	return (0);
}

int	eat(t_philo *philo)
{
	while (check_alive(philo->meta))
	{
		if (philo->meta->n_philos == 1)
			break ;
		if (grab_forks(philo))
		{
			philo->last_ate = get_time(philo->meta, 0);
			print_lock(philo, "is eating");
			philo->times_ate += 1;
			usleep(philo->meta->t_eat * 1000);
			handle_fork(philo->l_fork, DROP, philo);
			handle_fork(philo->r_fork, DROP, philo);
			break ;
		}
	}
	return (EXIT_SUCCESS);
}

int	think(t_philo *philo)
{
	print_lock(philo, "is thinking");
	usleep(10);
	return (EXIT_SUCCESS);
}
