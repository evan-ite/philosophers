/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/18 12:53:27 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// Error messages
# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_MEM "Error allocating memory"
# define ERR_MUTEX "Mutex error"
# define ERR_THD "Thread error"

// Structures
typedef struct s_philo {
	pthread_t		thread_id;
	int				id;
	long long		last_ate;
	int				l_fork[2];
	int				r_fork[2];
	struct s_meta	*meta;
}	t_philo;

typedef struct s_meta {
	pthread_t		monitor_id;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	int				all_alive;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
}	t_meta;

// Fuctions
int	init_meta(int argc, char **argv, t_meta *meta);
int	run(t_meta *meta);

// Philo utils
int	sleeping(t_philo *philo);
int	eat(t_philo *philo);
int	think(t_philo *philo);
int	check_death(t_philo *philo);

// Utils
int		exit_error(char *err_msg, char *src, int err_code, t_meta *meta);
long long	get_time(t_meta *, int start);
void	print_lock(t_philo *philo, char *state);
void	free_meta(t_meta *meta);

// Libft
void	*ft_calloc(size_t nmemb, size_t bytesize);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *s);

#endif
