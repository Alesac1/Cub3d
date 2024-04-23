/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:51:00 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:51:00 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_keyrelease(int keycode, t_game *game)
{
	// printf("keycode: %d\n", keycode);
	if (keycode == XK_w || keycode == XK_s)
		game->moves.move_speed = 0;
	if (keycode == XK_d || keycode == XK_a)
		game->moves.move_side_speed = 0;
	if (keycode == XK_w)
		game->moves.w = 0;
	if (keycode == XK_s)
		game->moves.s = 0;
	if (keycode == XK_d)
		game->moves.d = 0;
	if (keycode == XK_a)
		game->moves.a = 0;
	if (keycode == 113 || keycode == 114)
		game->moves.rot_speed = 0;
	if (keycode == XK_Left)
		game->moves.l = 0;
	if (keycode == XK_Right)
		game->moves.r = 0;
	// if (keycode == 61)
	// {
	// 	if (game->mlx.width * 2 <= 3840)
	// 	{
	// 		game->mlx.width *= 2;
	// 		game->mlx.height *= 2;
	// 	}
	// }
	// if (keycode == 45)
	// {
	// 	mlx_clear_window(game->mlx.mlx, game->mlx.window);
	// 	game->mlx.width /= 2;
	// 	game->mlx.height /= 2;
	// }
	return (1);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		click_x(game);
	handle_movement(keycode, game);
	if (keycode == XK_Left)
	{
		game->moves.l = 1;
		game->moves.rot_speed = -.05;
	}
	if (keycode == XK_Right)
	{
		game->moves.r = 1;
		game->moves.rot_speed = .05;
	}
	if (keycode == 101)
   		game->doors[(int)game->walls_data.c_y][(int)game->walls_data.c_x].direction = -1;
	return (1);
}

void	handle_movement(int keycode, t_game *game)
{
	if (keycode == XK_w)
	{
		game->moves.w = 1;
		game->moves.move_speed = .05;
	}
	if (keycode == XK_a)
	{
		game->moves.a = 1;
		game->moves.move_side_speed = .05;
	}
	if (keycode == XK_s)
	{
		game->moves.s = 1;
		game->moves.move_speed = -.05;
	}
	if (keycode == XK_d)
	{
		game->moves.d = 1;
		game->moves.move_side_speed = -.05;
	}
}
