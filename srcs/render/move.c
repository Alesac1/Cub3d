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

void	move_forward(t_game *game, t_walls *data)
{
	double	pos_x;
	double	pos_y;
	double	door_hitx;
	double	door_hity;

	pos_x = game->mlx.pos_x + game->mlx.dir_x * game->moves.move_speed;
	pos_y = game->mlx.pos_y + game->mlx.dir_y * game->moves.move_speed;
	door_hitx = pos_x - floor(pos_x);
	door_hity = pos_y - floor(pos_y);
	 if ((game->mlx.dir_x > 0) || (game->mlx.dir_y > 0 ))
			{
				if (data->c_side == 0)
				{
					if (door_hity > game->walls_data.doors.open)
						return ;
					// printf("ci sono0\n");
				}
				else if (data->c_side == 1)
				{
					if (door_hitx > game->walls_data.doors.open)
						return ;
					// printf("ci sono1\n");
				}
				// printf("mlx.dir_x : %f\n", game->mlx.dir_x);
				// printf("door_hitx : %f\n", door_hitx);
				// printf("game->walls_data.doors.open : %f\n", game->walls_data.doors.open);
				// printf("mlx.dir_y : %f\n", game->mlx.dir_y);
				// printf("door_hity : %f\n", door_hity);
				// printf("game->walls_data.doors.open : %f\n", game->walls_data.doors.open);
			}
	 if (game->map[(int)(game->mlx.pos_y)][(int)pos_x] != '1')
		game->mlx.pos_x += game->mlx.dir_x * game->moves.move_speed;
    if (game->map[(int)pos_y][(int)(game->mlx.pos_x)] != '1')
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
