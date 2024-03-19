/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:27:07 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/19 13:36:48 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_MEM "Error allocating memory"

int	check_input(int argc, char **argv);
int	exit_error(char *err_msg, char *src, int err_code);

// libft
void		*ft_calloc(size_t nmemb, size_t bytesize);
char		*ft_strjoin(const char *s1, const char *s2);
void		ft_putendl_fd(char *s, int fd);
int			ft_atoi(const char *s);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);

#endif
