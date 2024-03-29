/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:29:56 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/29 17:40:19 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

long long	get_time(t_meta *meta, int start)
{
	struct timeval	time;
	long long		time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000LL) + (time.tv_usec / 1000LL);
	if (!start)
		time_ms = time_ms - meta->start_time;
	return (time_ms);
}

int	check_death(t_philo *philo)
{
	if ((get_time(philo->meta, 0) - philo->last_ate) > philo->meta->t_die)
	{
		print_lock(philo, "is dead");
		sem_wait(philo->meta->print);
		return (1);
	}
	return (0);
}

int	check_times_ate(t_philo *philo)
{
	if (philo->meta->n_must_eat < 0)
		return (0);
	if (philo->times_ate < philo->meta->n_must_eat)
		return (0);
	return (1);
}

void	print_lock(t_philo *philo, char *state)
{
	sem_wait(philo->meta->print);
	printf("%lld %i %s\n", get_time(philo->meta, 0), philo->id + 1, state);
	sem_post(philo->meta->print);
}
