/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:51:46 by dde-giov          #+#    #+#             */
/*   Updated: 2024/04/23 16:59:42 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initminimap(t_game *game)
{
	int	i;

	i = 0;
	game->mmap.mmap.img = mlx_new_image(game->mlx.mlx, game->mlx.width / 4,
			game->mlx.width / 4);
	game->mmap.mmap.addr = mlx_get_data_addr(game->mmap.mmap.img,
			&game->mmap.mmap.bits_per_pixel, &game->mmap.mmap.line_length,
			&game->mmap.mmap.endian);
	game->mmap.map = (char **)malloc(sizeof(char *) * game->mmap.width);
	if (!game->mmap.map)
		print_error("Error! Malloc failed!\n", game, 0);
	while (i < game->mmap.width)
	{
		game->mmap.map[i] = (char *)malloc(sizeof(char) * game->mmap.width);
		if (!game->mmap.map[i])
			print_error("Error! Malloc failed!\n", game, 0);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->mmap.y = 0;
	create_minimap(game);
	while (y <= game->mlx.height)
	{
		x = 0;
		game->mmap.x = 0;
		while (x <= game->mlx.width)
		{
			print_mmap(game, x, y);
			// blend_pixel(game, x, y, 0.8);
			x++;
			if (x % 8 == 0)
				game->mmap.x++;
		}
		y++;
		if (y % 8 == 0)
			game->mmap.y++;
	}
}

void	blend_pixel(t_game *game, int x, int y, float alpha)
{
	unsigned int	blended_color;
	unsigned char	src_rgba[4];
	unsigned char	dst_rgba[4];
	int				i;

	src_rgba[0] = (get_pixel(game->mmap.mmap.img, x, y) >> 24) & 0xFF;
	src_rgba[1] = (get_pixel(game->mmap.mmap.img, x, y) >> 16) & 0xFF;
	src_rgba[2] = (get_pixel(game->mmap.mmap.img, x, y) >> 8) & 0xFF;
	src_rgba[3] = (get_pixel(game->mmap.mmap.img, x, y)) & 0xFF;
	dst_rgba[0] = (get_pixel(game->mlx.img.img, x, y) >> 24) & 0xFF;
	dst_rgba[1] = (get_pixel(game->mlx.img.img, x, y) >> 16) & 0xFF;
	dst_rgba[2] = (get_pixel(game->mlx.img.img, x, y) >> 8) & 0xFF;
	dst_rgba[3] = (get_pixel(game->mlx.img.img, x, y)) & 0xFF;
	while (i < 4)
	{
		dst_rgba[i] = (unsigned char)((1 - alpha)
				* dst_rgba[i] + alpha * src_rgba[i]);
		i++;
	}
	blended_color = (dst_rgba[0] << 24) | (dst_rgba[1] << 16)
		| (dst_rgba[2] << 8) | dst_rgba[3];
	my_mlx_pixel_put(game, game->mlx.img.img, x, y, blended_color);
}

void	print_mmap(t_game *game, int x, int y)
{
	if (game->mmap.map[game->mmap.y][game->mmap.x] == 'N')
		return ;
	if (game->mmap.map[game->mmap.y][game->mmap.x] == '1')
		my_mlx_pixel_put(game, &game->mlx.img, x, y, 0x000000);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == '0')
		my_mlx_pixel_put(game, &game->mlx.img, x, y, 0xFFFFFF);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == '2')
		my_mlx_pixel_put(game, &game->mlx.img, x, y, 0xFF0000);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == 'P')
		my_mlx_pixel_put(game, &game->mlx.img, x, y, 0x00FF00);
}

void	create_minimap(t_game *game)
{
	int	x;
	int	y;
	int	pos_x;
	int	pos_y;

	pos_x = game->mlx.pos_x;
	pos_y = game->mlx.pos_y;
	y = 0;
	printf("\n  MINIMAP:\n");
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			// printf(" width: %d height: %d\n", game->path.width, game->path.height);
			// printf("Map x: %d y: %d\n", pos_x - 4 + x, pos_y - 4 + y);
			// printf("Mmap x: %d y: %d\n", x, y);
			if (pos_x - 4 + x < 0 || pos_y - 4 + y < 0 || pos_x - 4 + x >= game->path.width || pos_y - 4 + y >= game->path.height)
				game->mmap.map[y][x] = 'N';
			else if (game->map[pos_y - 4 + y][pos_x - 4 + x] == '1')
				game->mmap.map[y][x] = '1';
			else if (game->map[pos_y - 4 + y][pos_x - 4 + x] == '0')
				game->mmap.map[y][x] = '0';
			else if (game->map[pos_y - 4 + y][pos_x - 4 + x] == '2')
				game->mmap.map[y][x] = '2';
			else if (game->map[pos_y - 4 + y][pos_x - 4 + x] == 'N'
				|| game->map[pos_y - 4 + y][pos_x - 4 + x] == 'S'
				|| game->map[pos_y - 4 + y][pos_x - 4 + x] == 'E'
				|| game->map[pos_y - 4 + y][pos_x - 4 + x] == 'W')
				game->mmap.map[y][x] = '0';
			printf("|%c|", game->mmap.map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
