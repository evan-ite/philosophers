/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:55 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/02 15:11:05 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_MEM "Error allocating memory"
# define ERR_MUTEX "Mutex error"
# define ERR_THD "Thread error"

typedef struct s_philo {
	pthread_t		thread_id;
	int				id;
	long long		last_ate;
	int				times_ate;
	int				l_fork;
	int				r_fork;
	struct s_meta	*meta;
}	t_philo;

typedef struct s_meta {
	pthread_t		monitor_id;
	int				monitor_flag;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	int				all_alive;
	pthread_mutex_t	alive;
	long long		start_time;
	t_philo			*philos;
	int				*philos_flag;
	pthread_mutex_t	*forks;
	int				*fork_flag;
	pthread_mutex_t	print;
	int				print_flag;
}	t_meta;

int			init_meta(int argc, char **argv, t_meta *meta);
int			run(t_meta *meta);
int			sleeping(t_philo *philo);
int			eat(t_philo *philo);
int			think(t_philo *philo);

// utils
int			check_death(t_philo *philo);
int			check_all_ate(t_meta *meta);
int			check_alive(t_meta *meta);
int			exit_error(char *err_msg, char *src, int err_code, t_meta *meta);
int			check_input(int argc, char **argv);
long long	get_time(t_meta *meta, int start);
void		print_lock(t_philo *philo, char *state);
void		free_meta(t_meta *meta);

// libft
void		*ft_calloc(size_t nmemb, size_t bytesize);
char		*ft_strjoin(const char *s1, const char *s2);
void		ft_putendl_fd(char *s, int fd);
int			ft_atoi(const char *s);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);

#endif
