/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:51:46 by dde-giov          #+#    #+#             */
/*   Updated: 2024/04/23 05:22:15 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initminimap(t_game *game)
{
	int	i;

	i = 0;
	printf("initminimap\n");
	game->mmap.mmap.img = mlx_new_image(game->mlx.mlx, game->mlx.width / 4,
			game->mlx.width / 4);
		printf("initminimap 1\n");
	game->mmap.mmap.addr = mlx_get_data_addr(game->mmap.mmap.img,
			&game->mmap.mmap.bits_per_pixel, &game->mmap.mmap.line_length,
			&game->mmap.mmap.endian);
	printf("initminimap 2\n");
	game->mmap.map = (char **)malloc(sizeof(char *) * game->mmap.width);
	if (!game->mmap.map)
		print_error("Error! Malloc failed!\n", game, 0);
		printf("initminimap 3\n");
	while (i < game->mmap.width)
	{
		game->mmap.map[i] = (char *)malloc(sizeof(char) * game->mmap.width);
		if (!game->mmap.map[i])
			print_error("Error! Malloc failed!\n", game, 0);
		printf("initminimap 4\n");
		i++;
	}
	printf("initminimap end\n");
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
			//blend_pixel(game, x, y, 0.8);
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
	//my_mlx_pixel_put(game, game->mlx.img.img, x, y, blended_color);
}

void	print_mmap(t_game *game, int x, int y)
{
	if (game->mmap.map[game->mmap.y][game->mmap.x] == 'N')
		return ;
	if (game->mmap.map[game->mmap.y][game->mmap.x] == '1')
		my_mlx_pixel_put(game, &game->mmap.mmap, x, y, 0x000000);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == '0')
		my_mlx_pixel_put(game, &game->mmap.mmap, x, y, 0xFFFFFF);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == '2')
		my_mlx_pixel_put(game, &game->mmap.mmap, x, y, 0xFF0000);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == 'P')
		my_mlx_pixel_put(game, &game->mmap.mmap, x, y, 0x00FF00);
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
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			if (pos_x - 4 + x < 0 || pos_y - 4 + y < 0)
				game->mmap.map[y][x] = 'N';
			if (game->map[pos_y - 4 + y][pos_x - 4 + x] == '1')
				game->mmap.map[y][x] = '1';
			else if (game->map[pos_y - 4 + y][pos_x - 4 + x] == '0')
				game->mmap.map[y][x] = '0';
			else if (game->map[pos_y - 4 + y][pos_x - 4 + x] == '2')
				game->mmap.map[y][x] = '2';
			else if (game->map[pos_y - 4 + y][pos_x - 4 + x] == 'N'
				|| game->map[pos_y - 4 + y][pos_x - 4 + x] == 'S'
				|| game->map[pos_y - 4 + y][pos_x - 4 + x] == 'E'
				|| game->map[pos_y - 4 + y][pos_x - 4 + x] == 'W')
				game->mmap.map[y][x] = 'P';
			x++;
		}
		y++;
	}
}
