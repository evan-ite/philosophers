/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:29:32 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/05 13:09:37 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	close_semaphores(t_meta *meta)
{
	if (meta->forks != SEM_FAILED)
	{
		sem_close(meta->forks);
		sem_unlink("/forks");
	}
	if (meta->print != SEM_FAILED)
	{
		sem_close(meta->print);
		sem_unlink("/print");
	}
	if (meta->stop != SEM_FAILED)
	{
		sem_close(meta->stop);
		sem_unlink("/stop");
	}
	if (meta->death != SEM_FAILED)
	{
		sem_close(meta->death);
		sem_unlink("/death");
	}
}

void	free_meta(t_meta *meta)
{
	int	i;

	if (meta)
	{
		close_semaphores(meta);
		if (meta->philos)
		{
			i = 0;
			while (i < meta->n_philos)
			{
				if (meta->philos[i].monitor_flag)
				{
					pthread_detach(meta->philos[i].monitor_id);
					meta->philos[i].monitor_flag = 0;
				}
				i++;
			}
			free(meta->philos);
		}
		free(meta);
	}
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
			exit(EXIT_FAILURE);
		}
		ft_putendl_fd(result, 2);
		free(result);
	}
	else if (err_msg)
		ft_putendl_fd(err_msg, 2);
	if (meta)
		free_meta(meta);
	err_code++;
	exit(EXIT_FAILURE);
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
