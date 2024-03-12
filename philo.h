/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/12 16:09:58 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Error messages
# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_MEM "Error allocating memory"
# define ERR_MUTEX "Mutex error"
# define ERR_THD "Thread error"

// Structures
typedef struct s_philo {
	pthread_t	id;
	int		state;
	int		l_fork;
	int		r_fork;
}	t_philo;

typedef struct s_meta {
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_meta;

// Fuctions
int	init_meta(int argc, char **argv, t_meta *meta);
int	run(t_meta *meta);

// Utils
int		exit_error(char *err_msg, char *src, int err_code, t_meta *meta);

// Libft
void	*ft_calloc(size_t nmemb, size_t bytesize);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *s);

#endif
