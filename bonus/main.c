/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:26:17 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/25 11:42:07 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"


int	main(int argc, char **argv)
{
	t_meta	*meta;

	meta = ft_calloc(1, sizeof(t_meta));
	if (!meta)
		exit_error(ERR_CHILD, NULL, -1, NULL);
	if (!check_input(argc, argv))
		exit_error(ERR_INPUT, NULL, 1, NULL);
	init_meta(argc, argv, meta);
	start_simulation(meta);
	free_meta(meta);
	return (EXIT_SUCCESS);
}
