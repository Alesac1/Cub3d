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
	float next_x;
	float next_y;

	next_x = game->mlx.pos_x + game->mlx.dir_x * game->moves.move_speed;
	next_y = game->mlx.pos_y + game->mlx.dir_y * game->moves.move_speed;
	moving(game, next_x, next_y);
}

void move_side(t_game *game)
{
	float next_x;
	float next_y;

	next_x = game->mlx.pos_x + game->mlx.plane_x * game->moves.move_side_speed;
	next_y = game->mlx.pos_y + game->mlx.plane_y * game->moves.move_side_speed;
	moving(game, next_x, next_y);
}

void moving(t_game *game, float next_x, float next_y)
{
	float hitx;
	float hity;

	hitx = next_x - floor(next_x);
	hity = next_y - floor(next_y);
	if (game->map[(int)next_y][(int)next_x] == '2')
	{
	if ((game->doors[(int)next_y][(int)next_x].side == 1 && hitx < game->doors[(int)next_y][(int)next_x].open) ||
				(game->doors[(int)next_y][(int)next_x].side == 0 && hity < game->doors[(int)next_y][(int)next_x].open))
			return;
	}
	if (game->map[(int)(game->mlx.pos_y)][(int)next_x] != '1')
		game->mlx.pos_x = next_x;
	if (game->map[(int)next_y][(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y = next_y;
}

int mouse_position(int x, int y, void *param)
{
	t_game *game;
	int half_width;
	double fov_factor;

	game = (t_game *)param;
	half_width = game->mlx.width / 2;
	fov_factor = (x - half_width) * 0.005;
	game->mlx.dir_x = sin(fov_factor);
	game->mlx.dir_y = cos(fov_factor);
	game->mlx.plane_x = -cos(fov_factor);
	game->mlx.plane_y = sin(fov_factor);

	return (0);
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
