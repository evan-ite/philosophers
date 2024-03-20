/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:26:17 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/20 14:35:17 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_meta	meta;

	check_input(argc, argv);
	init_meta(argc, argv, &meta);
	start_simulation(&meta);
	return (EXIT_SUCCESS);
}
