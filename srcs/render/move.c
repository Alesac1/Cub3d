/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:53:43 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:53:43 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_game *game)
{
	if (game->map[(int)(game->mlx.pos_y)]
			[(int)(game->mlx.pos_x + game->mlx.dir_x * game->moves.move_speed)] != '1')
		game->mlx.pos_x += game->mlx.dir_x * game->moves.move_speed;
	if (game->map
		[(int)(game->mlx.pos_y + game->mlx.dir_y * game->moves.move_speed)]
		[(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y += game->mlx.dir_y * game->moves.move_speed;
}


void	move_side(t_game *game)
{
	if (game->map[(int)(game->mlx.pos_y)]
			[(int)(game->mlx.pos_x + game->mlx.plane_x * game->moves.move_side_speed)]
				!= '1')
		game->mlx.pos_x += game->mlx.plane_x * game->moves.move_side_speed;
	if (game->map
		[(int)(game->mlx.pos_y + game->mlx.plane_y * game->moves.move_side_speed)]
		[(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y += game->mlx.plane_y * game->moves.move_side_speed;
}

void	rotate_camera(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->mlx.dir_x;
	old_plane_x = game->mlx.plane_x;
	game->mlx.dir_x = game->mlx.dir_x * cos(game->moves.rot_speed)
		- game->mlx.dir_y * sin(game->moves.rot_speed);
	game->mlx.dir_y = old_dir_x * sin(game->moves.rot_speed)
		+ game->mlx.dir_y * cos(game->moves.rot_speed);
	game->mlx.plane_x = game->mlx.plane_x * cos(game->moves.rot_speed)
		- game->mlx.plane_y * sin(game->moves.rot_speed);
	game->mlx.plane_y = old_plane_x * sin(game->moves.rot_speed)
		+ game->mlx.plane_y * cos(game->moves.rot_speed);
}
