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
	float player_relative_pos_x;
	float player_relative_pos_y;

	next_x = game->mlx.pos_x + game->mlx.dir_x * game->moves.move_speed;
	next_y = game->mlx.pos_y + game->mlx.dir_y * game->moves.move_speed;

	player_relative_pos_x = next_x - floor(next_x);
	player_relative_pos_y = next_y - floor(next_y);
	if (game->map[(int)next_y][(int)next_x] == '2')
	{
		if ((game->walls_data.doors.side == 1 && player_relative_pos_x < game->walls_data.doors.open) ||
			(game->walls_data.doors.side == 0 && player_relative_pos_y < game->walls_data.doors.open))
		return;
	}
	if (game->map[(int)(game->mlx.pos_y)][(int)next_x] != '1')
		game->mlx.pos_x = next_x;
	if (game->map[(int)next_y][(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y = next_y;
}

void move_side(t_game *game)
{
	float next_x;
	float next_y;
	float door_hitx;
	float door_hity;

	next_x = game->mlx.pos_x + game->mlx.plane_x * game->moves.move_side_speed;
	next_y = game->mlx.pos_y + game->mlx.plane_y * game->moves.move_side_speed;
	door_hitx = next_x - floor(next_x);
	door_hity = next_y - floor(next_y);
	if (game->map[(int)next_y][(int)next_x] == '2')
	{
	if ((game->walls_data.doors.side == 1 && door_hitx < game->walls_data.doors.open) ||
				(game->walls_data.doors.side == 0 && door_hity < game->walls_data.doors.open))
			return;
	}
	if (game->map[(int)(game->mlx.pos_y)][(int)next_x] != '1')
		game->mlx.pos_x = next_x;
	if (game->map[(int)next_y][(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y = next_y;
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

		// void move_forward(t_game *game)
		// {
		// float next_x;
		// float next_y;
		// float player_relative_pos_x;
		// float player_relative_pos_y;

		// next_x = game->mlx.pos_x + game->mlx.dir_x * game->moves.move_speed;
		// next_y = game->mlx.pos_y + game->mlx.dir_y * game->moves.move_speed;

		// // Calcola la posizione relativa del giocatore rispetto alla porta
		// player_relative_pos_x = next_x - floor(next_x);
		// player_relative_pos_y = next_y - floor(next_y);

		// // Controlla separatamente per la direzione X
		// if (game->map[(int)(game->mlx.pos_y)][(int)next_x] != '1')
		// {
		// 	if (game->map[(int)(game->mlx.pos_y)][(int)next_x] == '2')
		// 	{
		// 		if (game->walls_data.doors.side == 1 && player_relative_pos_x > game->walls_data.doors.open)
		// 		{
		// 			game->mlx.pos_x = next_x;
		// 		}  
		// 	}
		// 	else
		// 	{
		// 		game->mlx.pos_x = next_x;
		// 	}
		// }

		// // Controlla separatamente per la direzione Y
		// if (game->map[(int)next_y][(int)(game->mlx.pos_x)] != '1')
		// {
		// 	if (game->map[(int)next_y][(int)(game->mlx.pos_x)] == '2')
		// 	{
		// 		if (game->walls_data.doors.side == 0 && player_relative_pos_y > game->walls_data.doors.open)
		// 		{
		// 			game->mlx.pos_y = next_y;
		// 		}
		// 	}
		// 	else
		// 	{
		// 		game->mlx.pos_y = next_y;
		// 	}
		// }