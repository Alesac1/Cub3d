/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:52:57 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:52:57 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
int	game_loop(t_game *game)
{
	game->walls_data.doors.open += 0.01;
	if (game->walls_data.doors.open >= 1)
		game->walls_data.doors.open = 0	;
	if (game->moves.w == 1 || game->moves.s == 1)
		move_forward(game);
	if (game->moves.a == 1 || game->moves.d == 1)
		move_side(game);
	if (game->moves.l == 1 || game->moves.r == 1)
		rotate_camera(game);
	render_things(game);
	return (0);
}

void	render_things(t_game *game)
{
	render_floor_ceiling(game);
	render_walls(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.window, game->mlx.img.img, 0, 0);
}

