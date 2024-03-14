/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisevaniterson <elisevaniterson@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:26:27 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/14 09:54:47 by elisevanite      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_meta(t_meta *meta)
{
	int	i;

	if (&meta->print_mutex)
		pthread_mutex_destroy(&meta->print_mutex);
	if (meta->forks)
	{
		i = 0;
		while (&meta->forks[i])
			pthread_mutex_destroy(&meta->forks[i++]);
	}
	if (meta->philos)
	{
		i = 0;
		while (meta->philos[i].thread_id)
			pthread_detach(meta->philos[i++].thread_id);
		free(meta->philos);
	}
	if (meta->monitor_id)
		pthread_detach(meta->monitor_id);
	free(meta);
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
			return(EXIT_FAILURE);
		}
		ft_putendl_fd(result, 2);
		free(result);
	}
	else
		ft_putendl_fd(err_msg, 2);
	if (meta)
		free_meta(meta);
	return(err_code);
}
