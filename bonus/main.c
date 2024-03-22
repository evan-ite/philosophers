/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:26:17 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/22 12:15:37 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

t_meta	meta;

int	main(int argc, char **argv)
{
	if (!check_input(argc, argv))
		exit_error(ERR_INPUT, NULL, 1, NULL);
	init_meta(argc, argv, &meta);
	start_simulation(&meta);
	return (EXIT_SUCCESS);
}
