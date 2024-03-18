/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:19:56 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/18 15:36:23 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_meta	*meta;

	if (!check_input(argc, argv))
		return (exit_error(ERR_INPUT, NULL, 1, NULL));
	meta = ft_calloc(1, sizeof(t_meta));
	if (!meta)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	if (init_meta(argc, argv, meta))
		return (EXIT_FAILURE);
	if (run(meta))
		return (EXIT_FAILURE);
	free_meta(meta);
	if (meta)
		free(meta);
	return (EXIT_SUCCESS);
}
