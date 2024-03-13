/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:19:56 by evan-ite          #+#    #+#             */
/*   Updated: 2024/03/13 12:56:00 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_meta	*meta;

	if (argc < 5 || argc > 6)
		return (exit_error(ERR_INPUT, NULL, 1, NULL));
	meta = ft_calloc(1, sizeof(t_meta));
	if (!meta)
		return (exit_error(ERR_MEM, NULL, 2, meta));
	if (init_meta(argc, argv, meta))
		return (exit_error("", NULL, 1, meta));
	if (run(meta))
		return (exit_error("", NULL, 1, meta));
}
