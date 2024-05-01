/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:07:46 by dde-giov          #+#    #+#             */
/*   Updated: 2024/05/01 22:47:06 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	freemmap(t_game *game)
{
	int	i;

	i = 0;
	while (i <= game->mmap.size)
	{
		free(game->mmap.map[i]);
		i++;
	}
	free(game->mmap.map);
	mlx_destroy_image(game->mlx.mlx, game->mmap.mmap.img);
}

void	mmap_assign(t_game *game, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)game->mlx.pos_x - game->mmap.size / 2 + 1;
	pos_y = (int)game->mlx.pos_y - game->mmap.size / 2 + 1;
	if (pos_x + x < 0 || pos_y + y < 0 || pos_x + x >= game->p.width
		|| pos_y + y >= game->p.height
		|| x >= game->p.width || y >= game->p.height)
		game->mmap.map[y][x] = 'N';
	else if (game->map[pos_y + y][pos_x + x] == '1')
		game->mmap.map[y][x] = '1';
	else if (game->map[pos_y + y][pos_x + x] == '0')
		game->mmap.map[y][x] = '0';
	else if (game->map[pos_y + y][pos_x + x] == '2')
		game->mmap.map[y][x] = '2';
	else if (game->map[pos_y + y][pos_x + x] == 'N'
				|| game->map[pos_y + y][pos_x + x] == 'S'
				|| game->map[pos_y + y][pos_x + x] == 'E'
				|| game->map[pos_y + y][pos_x + x] == 'W')
		game->mmap.map[y][x] = '0';
	else
		game->mmap.map[y][x] = 'N';
}
