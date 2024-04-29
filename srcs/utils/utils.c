/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:40:31 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:40:31 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	ft_double(int b, double t, double f)
{
	if (b)
		return (t);
	return (f);
}

void	free_path(t_game *game)
{
	free(game->path.file_name);
	if (game->path.allocated >= 1)
		free(game->path.north);
	if (game->path.allocated >= 2)
		free(game->path.east);
	if (game->path.allocated >= 3)
		free(game->path.south);
	if (game->path.allocated >= 4)
		free(game->path.west);
	if (game->path.allocated >= 5)
		free(game->path.cealing);
	if (game->path.allocated >= 6)
		free(game->path.floor);
}

void	close_all(t_game *game, int r)
{
	int	i;

	if (r == 0)
		exit(0);
	free_path(game);
	if (r != 3)
		exit(0);
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(0);
}

int	click_x(t_game *game)
{
	mlx_destroy_image(game->mlx.mlx, game->mlx.no.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.so.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.we.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.ea.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.door.img);
	mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	mlx_destroy_window(game->mlx.mlx, game->mlx.window);
	mlx_destroy_display(game->mlx.mlx);
	close_all(game, 3);
	return (0);
}
