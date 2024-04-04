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

void	start_game(t_game *game)
{
	mlx_hook(game->mlx.window, 17, 0, &click_x, game);
	mlx_loop_hook(game->mlx.mlx, &game_loop, game);
	mlx_hook(game->mlx.window, 3, 1L << 1, &handle_keyrelease, game);
	mlx_hook(game->mlx.window, 2, 1L << 0, &handle_keypress, game);
	mlx_loop(game->mlx.mlx);
}

int	main(int argc, char const *argv[])
{
	int		fd;
	t_game	game;

	check_args(&game, argc, argv, &fd);
	// print_struct(&game);
	init_game(&game);
	start_game(&game);
	close_all(&game, 3);
	exit(0);
	return (0);
}
