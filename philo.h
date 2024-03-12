/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/12 12:29:27 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
					time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_MEM "Error allocating memory"

int	exit_error(char *err_msg, char *src, int err_code);

#endif
