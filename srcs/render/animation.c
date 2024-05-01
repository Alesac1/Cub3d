/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:34:34 by dde-giov          #+#    #+#             */
/*   Updated: 2024/05/01 21:57:14 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	animation(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->p.height)
	{
		x = 0;
		while (x < game->p.width)
		{
			door_anim(game, x, y);
			x++;
		}
		y++;
	}
}

void	door_anim(t_game *game, int x, int y)
{
	if (game->doors[y][x].door == 0)
		return ;
	if (game->doors[y][x].direction == 1)
		game->doors[y][x].open += 0.01;
	else if (game->doors[y][x].direction == -1)
		game->doors[y][x].open -= 0.01;
	if (game->doors[y][x].open <= 0)
	{
		game->doors[y][x].direction = 1;
		game->doors[y][x].open = 0;
	}
	else if (game->doors[y][x].open >= 1)
	{
		game->doors[y][x].direction = 0;
		game->doors[y][x].open = 1;
	}
}

void	set_pos(t_game *game)
{
	if (game->spawn.direction == 'W')
	{
		game->mlx.dir_x = -1;
		game->mlx.plane_y = 0.66;
	}
	if (game->spawn.direction == 'E')
	{
		game->mlx.dir_x = 1;
		game->mlx.plane_y = -0.66;
	}
	if (game->spawn.direction == 'N')
	{
		game->mlx.dir_y = -1;
		game->mlx.plane_x = -0.66;
	}
	if (game->spawn.direction == 'S')
	{
		game->mlx.dir_y = 1;
		game->mlx.plane_x = 0.66;
	}
}
