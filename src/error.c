/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:26:27 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/12 12:29:05 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	exit_error(char *err_msg, char *src, int err_code)
{
	char	*result;

	if (src)
	{
		result = ft_strjoin(src, err_msg);
		if (!result)
		{
			ft_putendl_fd(ERR_MEM, 2);
			exit(-1);
		}
		ft_putendl_fd(result, 2);
		free(result);
	}
	else
		ft_putendl_fd(err_msg, 2);
	exit(err_code);
}
