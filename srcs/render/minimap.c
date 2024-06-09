/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:51:46 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/09 21:42:04 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initminimap(t_game *game)
{
	int	i;

	i = 0;
	game->mmap.width = game->mlx.width / 8;
	game->mmap.sprite_size = game->mmap.width / game->mmap.size;
	game->mmap.mmap.img = mlx_new_image(game->mlx.mlx, game->mmap.width,
			game->mmap.width);
	game->mmap.mmap.addr = mlx_get_data_addr(game->mmap.mmap.img,
			&game->mmap.mmap.bits_per_pixel, &game->mmap.mmap.line_length,
			&game->mmap.mmap.endian);
	game->mmap.map = (char **)malloc(sizeof(char *) * (game->mmap.size + 1));
	if (!game->mmap.map)
		print_error("Error\n Malloc failed!\n", game, 0);
	while (i < (game->mmap.size + 1))
	{
		game->mmap.map[i] = (char *)malloc(sizeof(char)
				* (game->mmap.size + 1));
		if (!game->mmap.map[i])
			print_error("Error\n Malloc failed!\n", game, 0);
		i++;
	}
	create_minimap(game);
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->mmap.y = 0;
	initminimap(game);
	while (y <= game->mmap.width)
	{
		x = 0;
		game->mmap.x = 0;
		while (x <= game->mmap.width)
		{
			print_mmap(game, x, y);
			blend_pixel(game, x, y);
			x++;
			if (x % game->mmap.sprite_size == 0 && game->mmap.x + 1
				< game->mmap.size)
				game->mmap.x++;
		}
		y++;
		if (y % game->mmap.sprite_size == 0 && game->mmap.y + 1
			< game->mmap.size)
			game->mmap.y++;
	}
	freemmap(game);
}

void	print_mmap(t_game *game, int x, int y)
{
	if (game->mmap.map[game->mmap.y][game->mmap.x] == 'N')
		return ;
	if (game->mmap.map[game->mmap.y][game->mmap.x] == '1')
		my_mlx_pixel_put(&game->mmap.mmap, x, y, 0x000000);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == '0')
		my_mlx_pixel_put(&game->mmap.mmap, x, y, 0xFFFFFF);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == '2')
		my_mlx_pixel_put(&game->mmap.mmap, x, y, 0xFF0000);
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == 'P')
		my_mlx_pixel_put(&game->mmap.mmap, x, y, 0x00FF00);
	if (x >= game->mmap.width / 2 - game->mmap.sprite_size
		&& y >= game->mmap.width / 2 - game->mmap.sprite_size
		&& x < game->mmap.width / 2 && y < game->mmap.width / 2)
		my_mlx_pixel_put(&game->mmap.mmap, x, y, 0x0000FF);
}

void	blend_pixel(t_game *game, int x, int y)
{
	unsigned char	src_rgba[4];
	unsigned char	dst_rgba[4];
	float			alpha;
	int				i;

	src_rgba[0] = (get_pixel(&game->mmap.mmap, x, y) >> 24) & 0xFF;
	src_rgba[1] = (get_pixel(&game->mmap.mmap, x, y) >> 16) & 0xFF;
	src_rgba[2] = (get_pixel(&game->mmap.mmap, x, y) >> 8) & 0xFF;
	src_rgba[3] = (get_pixel(&game->mmap.mmap, x, y)) & 0xFF;
	dst_rgba[0] = (get_pixel(&game->mlx.img, x, y) >> 24) & 0xFF;
	dst_rgba[1] = (get_pixel(&game->mlx.img, x, y) >> 16) & 0xFF;
	dst_rgba[2] = (get_pixel(&game->mlx.img, x, y) >> 8) & 0xFF;
	dst_rgba[3] = (get_pixel(&game->mlx.img, x, y)) & 0xFF;
	if (game->mmap.map[game->mmap.y][game->mmap.x] == 'N')
		alpha = 0;
	else if (game->mmap.map[game->mmap.y][game->mmap.x] == '0')
		alpha = 0.3;
	else
		alpha = 1;
	i = -1;
	while (++i < 4)
		dst_rgba[i] = (unsigned char)((1 - alpha)
				* dst_rgba[i] + alpha * src_rgba[i]);
	my_mlx_pixel_put(&game->mlx.img, x, y, ((dst_rgba[0] << 24
				) | (dst_rgba[1] << 16) | (dst_rgba[2] << 8) | dst_rgba[3]));
}

void	create_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->mmap.size)
	{
		x = 0;
		while (x < game->mmap.size)
		{
			mmap_assign(game, x, y);
			x++;
		}
		y++;
	}
}
