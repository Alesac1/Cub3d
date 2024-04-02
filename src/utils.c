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

#include "../includes/cub3d.h"

double	ft_double(int b, double t, double f)
{
	if (b)
		return (t);
	return (f);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREENWIDTH || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	get_addresses(t_game *game)
{
	game->mlx.ea.addr = mlx_get_data_addr(game->mlx.ea.img, 
			&game->mlx.ea.bits_per_pixel, &game->mlx.ea.line_length, 
			&game->mlx.ea.endian);
	game->mlx.so.addr = mlx_get_data_addr(game->mlx.so.img, 
			&game->mlx.so.bits_per_pixel, &game->mlx.so.line_length, 
			&game->mlx.so.endian);
	game->mlx.we.addr = mlx_get_data_addr(game->mlx.we.img, 
			&game->mlx.we.bits_per_pixel, &game->mlx.we.line_length, 
			&game->mlx.we.endian);
	game->mlx.no.addr = mlx_get_data_addr(game->mlx.no.img, 
			&game->mlx.no.bits_per_pixel, &game->mlx.no.line_length, 
			&game->mlx.no.endian);
}

void	close_all(t_game *game, int r)
{
	int i;

	if (r == 0)
		exit(0);
	free(game->path.east);
	free(game->path.north);
	free(game->path.west);
	free(game->path.south);
	free(game->path.cealing);
	free(game->path.floor);
	free(game->path.file_name);
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

void	free_rgb(char **rgb)
{
	int i;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}