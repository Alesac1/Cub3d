/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:56:10 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:56:10 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*dest;

	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
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

void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREENWIDTH || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
