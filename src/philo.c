/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:27:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/12 16:11:02 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start_philo(void *meta)
{
	printf("PARTY\n");
	return (meta);
}

int	run(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_create(&meta->philos[i].id, NULL, start_philo, meta) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		i++;
	}
	i = 0;
	while (i < meta->n_philos)
	{
		if (pthread_join(meta->philos[i].id, NULL) != 0)
			return (exit_error(ERR_THD, NULL, 3, meta));
		i++;
	}
	printf("finished all threads \n");
	return (EXIT_SUCCESS);
}
