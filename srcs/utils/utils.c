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
	if (game->p.file_name != DEFAULT)
		free(game->p.file_name);
	if (game->p.n != DEFAULT)
		free(game->p.n);
	if (game->p.e != DEFAULT)
		free(game->p.e);
	if (game->p.s != DEFAULT)
		free(game->p.s);
	if (game->p.w != DEFAULT)
		free(game->p.w);
	if (game->p.cealing != DEFAULT)
		free(game->p.cealing);
	if (game->p.floor != DEFAULT)
		free(game->p.floor);
}

void	close_all(t_game *game, int r)
{
	int	i;

	free_path(game);
	if (r != 3)
		exit(0);
	i = 0;
	while (i < game->p.height)
	{
		free(game->map[i]);
		if (game->p.mmap_alloc > 1)
			free(game->doors[i]);
		i++;
	}
	if (game->p.mmap_alloc)
		free(game->doors);
	free(game->map);
	exit(0);
}

int	click_x(t_game *game)
{
	if (game->mlx.no.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.no.img);
	if (game->mlx.so.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.so.img);
	if (game->mlx.we.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.we.img);
	if (game->mlx.ea.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.ea.img);
	if (game->mlx.door.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.door.img);
	if (game->mlx.img.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	if (game->mlx.window)
		mlx_destroy_window(game->mlx.mlx, game->mlx.window);
	if (game->mlx.mlx)
		mlx_destroy_display(game->mlx.mlx);
	close_all(game, 3);
	return (0);
}
