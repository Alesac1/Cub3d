/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:38:28 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 16:38:28 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_vars(t_game *game)
{
	game->mlx.pos_x = game->spawn.x + 0.5;
	game->mlx.pos_y = game->spawn.y + 0.5;
	game->mlx.dir_x = 0;
	game->mlx.dir_y = 0;
	game->mlx.plane_x = 0;
	game->mlx.plane_y = 0;
	game->mlx.width = 3840;
	game->mlx.height = 2160;
	game->mlx.init_w = game->mlx.width;
	game->mlx.init_h = game->mlx.height;
	set_pos(game);
	game->moves.rot_speed = 0;
	game->moves.move_speed = 0;
	game->moves.w = 0;
	game->moves.a = 0;
	game->moves.s = 0;
	game->moves.d = 0;
	game->moves.l = 0;
	game->moves.r = 0;
	game->moves.open_all = 0;
	game->mmap.size = 16;
	game->mmap.width = game->mlx.width / 8;
	game->mmap.sprite_size = game->mmap.width / game->mmap.size;
}

void	load_imgs(t_game *game)
{
	int	z;
	int	r;

	r = 64;
	z = 64;
	game->mlx.ea.img = mlx_xpm_file_to_image(game->mlx.mlx, game->p.e, &r, &z);
	if (!game->mlx.ea.img)
		print_error("ERROR. Invalid textures.", game, 0);
	game->mlx.so.img = mlx_xpm_file_to_image(game->mlx.mlx, game->p.s, &r, &z);
	if (!game->mlx.so.img)
		print_error("ERROR. Invalid textures.", game, 0);
	game->mlx.we.img = mlx_xpm_file_to_image(game->mlx.mlx, game->p.w, &r, &z);
	if (!game->mlx.we.img)
		print_error("ERROR. Invalid textures.", game, 0);
	game->mlx.no.img = mlx_xpm_file_to_image(game->mlx.mlx, game->p.n, &r, &z);
	if (!game->mlx.no.img)
		print_error("ERROR. Invalid textures.", game, 0);
	game->mlx.door.img = mlx_xpm_file_to_image(game->mlx.mlx,
			"./textures/door.xpm", &r, &z);
	if (!game->mlx.door.img)
		print_error("ERROR. Invalid textures.", game, 0);
	get_addresses(game);
}

void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	game->mlx.img.img
		= mlx_new_image(game->mlx.mlx, game->mlx.width, game->mlx.height);
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.img,
			&game->mlx.img.bits_per_pixel, &game->mlx.img.line_length,
			&game->mlx.img.endian);
	game->mlx.window = mlx_new_window(game->mlx.mlx, game->mlx.width,
			game->mlx.height, "CUB'TRE'D");
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.window, game->mlx.img.img,
		0, 0);
}

	//render_things(game);
void	init_game(t_game *game)
{
	set_vars(game);
	init_mlx(game);
	load_imgs(game);
}

void	init_struct(t_game *game)
{
	game->p.n = DEFAULT;
	game->p.w = DEFAULT;
	game->p.e = DEFAULT;
	game->p.s = DEFAULT;
	game->p.cealing = DEFAULT;
	game->p.floor = DEFAULT;
	game->p.width = DEFAULT;
	game->p.height = DEFAULT;
	game->p.allocated = 0;
	game->p.mmap_alloc = 0;
	game->spawn.direction = 'I';
}

//void	set_pos(t_game *game)
//{
//	if (game->spawn.direction == 'W')
//	{
//		game->mlx.dir_x = -1;
//		game->mlx.plane_y = 0.66;
//	}
//	if (game->spawn.direction == 'E')
//	{
//		game->mlx.dir_x = 1;
//		game->mlx.plane_y = -0.66;
//	}
//	if (game->spawn.direction == 'N')
//	{
//		game->mlx.dir_y = -1;
//		game->mlx.plane_x = -0.66;
//	}
//	if (game->spawn.direction == 'S')
//	{
//		game->mlx.dir_y = 1;
//		game->mlx.plane_x = 0.66;
//	}
//}
