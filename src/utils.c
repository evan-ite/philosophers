/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:43:32 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/13 12:51:33 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_lock(t_philo *philo, char *state)
{
	// pthread_mutex_lock(&philo->meta->print_mutex);
	printf("%lld %i is %s\n", get_time(philo->meta), philo->id, state);
	// pthread_mutex_unlock(&philo->meta->print_mutex);
}
