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
	move_release(game, keycode);
	if (keycode == 45 && game->mmap.size <= 16)
		game->mmap.size *= 2;
	if (keycode == 61 && game->mmap.size > 4)
		game->mmap.size /= 2;
	if (keycode == 93 && game->mlx.width * 2 <= game->mlx.init_w)
	{
		game->mlx.width *= 2;
		game->mlx.height *= 2;
	}
	if (keycode == 91 && game->mlx.width / 2 >= 400)
	{
		black_screen(game);
		game->mlx.width /= 2;
		game->mlx.height /= 2;
	}
	return (1);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307)
		click_x(game);
	handle_movement(keycode, game);
	if (keycode == XK_LEFT)
	{
		game->moves.l = 1;
		game->moves.rot_speed = -.05;
	}
	if (keycode == XK_RIGHT)
	{
		game->moves.r = 1;
		game->moves.rot_speed = .05;
	}
	if (keycode == 101)
		game->doors[(int)game->wall.c_y]
		[(int)game->wall.c_x].direction = -1;
	if (keycode == 116)
		game->moves.open_all = 1;
	return (1);
}

void	handle_movement(int keycode, t_game *game)
{
	if (keycode == XK_W || keycode == XK_UP)
	{
		game->moves.w = 1;
		game->moves.move_speed = .05;
	}
	if (keycode == XK_A)
	{
		game->moves.a = 1;
		game->moves.move_side_speed = .05;
	}
	if (keycode == XK_S || keycode == XK_DOWN)
	{
		game->moves.s = 1;
		game->moves.move_speed = -.05;
	}
	if (keycode == XK_D)
	{
		game->moves.d = 1;
		game->moves.move_side_speed = -.05;
	}
}

void	move_release(t_game *game, int keycode)
{
	if (keycode == XK_W || keycode == XK_S || keycode == XK_UP
		|| keycode == XK_DOWN)
		game->moves.move_speed = 0;
	if (keycode == XK_D || keycode == XK_A)
		game->moves.move_side_speed = 0;
	if (keycode == XK_W || keycode == XK_UP)
		game->moves.w = 0;
	if (keycode == XK_S || keycode == XK_DOWN)
		game->moves.s = 0;
	if (keycode == XK_D)
		game->moves.d = 0;
	if (keycode == XK_A)
		game->moves.a = 0;
	if (keycode == 113 || keycode == 114)
		game->moves.rot_speed = 0;
	if (keycode == XK_LEFT)
		game->moves.l = 0;
	if (keycode == XK_RIGHT)
		game->moves.r = 0;
	if (keycode == XK_LEFT || keycode == XK_RIGHT)
		game->moves.rot_speed = 0;
}
