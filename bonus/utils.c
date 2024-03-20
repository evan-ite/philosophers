/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:29:56 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 11:37:43 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
		philo->meta->all_alive = 0;
		return (1);
	}
	return (0);
}

int	check_all_ate(t_meta *meta)
{
	int	i;

	if (meta->n_must_eat < 0)
		return (0);
	i = 0;
	while (i < meta->n_philos)
	{
		if (meta->philos[i].times_ate < meta->n_must_eat)
			return (0);
		i++;
	}
	meta->all_alive = 0;
	return (1);
}

void	print_lock(t_philo *philo, char *state)
{
	if (!philo->meta->all_alive)
		return ;
	sem_wait(&philo->meta->print);
	printf("%lld %i %s\n", get_time(philo->meta, 0), philo->id + 1, state);
	sem_post(&philo->meta->print);
}