/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:43:32 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/14 09:34:46 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time(t_meta *meta, int start)
{
	struct timeval	time;
	long long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000LL) + (time.tv_usec / 1000LL);
	if (!start)
		time_ms = time_ms - meta->start_time;
	return (time_ms);
}

void	print_lock(t_philo *philo, char *state)
{
	if (!philo->meta->all_alive)
		return ;
	pthread_mutex_lock(&philo->meta->print_mutex);
	printf("%lld %i is %s\n", get_time(philo->meta, 0), philo->id, state);
	pthread_mutex_unlock(&philo->meta->print_mutex);
}
