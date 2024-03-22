/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:27:07 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/22 13:06:53 by evan-ite         ###   ########.fr       */
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
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

# define ERR_INPUT "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_MEM "Error allocating memory"
# define ERR_SEM "Error creating semaphore"
# define ERR_CHILD "Error creating child process"
# define ERR_THD "Thread error"

typedef struct s_philo {
	int				pid;
	int				id;
	long long		last_ate;
	int				times_ate;
	struct s_meta	*meta;
	pthread_t		monitor_id;
	int				monitor_flag;
}	t_philo;

typedef struct s_meta {
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	int				all_alive;
	long long		start_time;
	t_philo			*philos;
	sem_t			forks;
	int				fork_flag;
	sem_t			print;
	int				print_flag;
}	t_meta;

// simulation
int	init_meta(int argc, char **argv, t_meta *meta);
int	check_input(int argc, char **argv);
int	exit_error(char *err_msg, char *src, int err_code, t_meta *meta);
long long	get_time(t_meta *meta, int start);
int	check_death(t_philo *philo);
int	check_all_ate(t_philo *philo);
void	print_lock(t_philo *philo, char *state);
void	start_simulation(t_meta *meta);
void	run_philo(t_philo *philo);
void	child_process(t_philo *philo);
void	kill_children(t_meta *meta);


// libft
void		*ft_calloc(size_t nmemb, size_t bytesize);
char		*ft_strjoin(const char *s1, const char *s2);
void		ft_putendl_fd(char *s, int fd);
int			ft_atoi(const char *s);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);

#endif
