/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:27:39 by dde-giov          #+#    #+#             */
/*   Updated: 2024/04/29 14:47:19 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	door_matrix(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->doors = malloc(sizeof(t_obj *) * game->p.height);
	while (i < game->p.height)
	{
		j = 0;
		game->doors[i] = malloc(sizeof(t_obj) * game->p.width);
		while (j < game->p.width)
		{
			if (game->map[i][j] == '2')
				game->doors[i][j].door = 1;
			else
				game->doors[i][j].door = 0;
			game->doors[i][j].hit_x = 0;
			game->doors[i][j].hit_y = 0;
			game->doors[i][j].open = 1;
			game->doors[i][j].side = 0;
			game->doors[i][j].direction = 0;
			j++;
		}
		i++;
	}
}
