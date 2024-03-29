/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:26:27 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/29 17:39:20 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_meta(t_meta *meta)
{
	int	i;

	pthread_mutex_destroy(&meta->alive);
	if (meta->print_flag == 1)
		pthread_mutex_destroy(&meta->print);
	if (meta->fork_flag)
	{
		i = 0;
		while (meta->fork_flag[i])
			pthread_mutex_destroy(&meta->forks[i++]);
		free(meta->fork_flag);
	}
	if (meta->philos_flag)
	{
		i = 0;
		while (meta->philos_flag[i])
			pthread_detach(meta->philos[i++].thread_id);
		free(meta->philos_flag);
	}
	if (meta->monitor_flag)
		pthread_detach(meta->monitor_id);
	if (meta->forks)
		free(meta->forks);
	if (meta->philos)
		free(meta->philos);
}

int	exit_error(char *err_msg, char *src, int err_code, t_meta *meta)
{
	char	*result;

	if (src)
	{
		result = ft_strjoin(src, err_msg);
		if (!result)
		{
			ft_putendl_fd(ERR_MEM, 2);
			return (EXIT_FAILURE);
		}
		ft_putendl_fd(result, 2);
		free(result);
	}
	else if (err_msg)
		ft_putendl_fd(err_msg, 2);
	if (meta)
	{
		free_meta(meta);
		free(meta);
	}
	return (err_code);
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
