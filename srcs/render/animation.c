/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:34:34 by dde-giov          #+#    #+#             */
/*   Updated: 2024/04/20 19:56:55 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    animation(t_game *game)
{
	int     x;
	int     y;

	y = 0;
	while (y < game->path.height)
	{
		x = 0;
		while (x < game->path.width)
		{
			if (game->doors[y][x].door == 0)
			{
				x++;
				continue;
			}
			if (game->doors[y][x].direction == 1)
			{
				printf("closing\n");
				game->doors[y][x].open += 0.01;
			}
			else if (game->doors[y][x].direction == -1)
			{
				printf("opening\n");
				game->doors[y][x].open -= 0.01;
			}
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
			x++;
		}
		y++;
	}
}
