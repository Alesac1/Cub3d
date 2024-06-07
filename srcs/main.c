/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:34:07 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 16:34:07 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char const *argv[])
{
	int		fd;
	t_game	game;

	check_args(&game, argc, argv, &fd);
	init_game(&game);
	start_game(&game);
	close_all(&game, 3);
	exit(0);
	return (0);
}
