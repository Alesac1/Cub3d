/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:48:47 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:48:47 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_floor_ceiling(t_game *game)
{
	int	y;
	int	x;

	y = game->mlx.height / 2 + 1;
	while (y < game->mlx.height)
	{
		x = 0;
		while (x < game->mlx.width)
		{
			my_mlx_pixel_put(&game->mlx.img, game->mlx.width - x,
				y, game->floor_color.hex);
			my_mlx_pixel_put(&game->mlx.img, game->mlx.width - x,
				game->mlx.height - y - 1, game->ceiling_color.hex);
			x++;
		}
		y++;
	}
}

void	render_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->mlx.width)
	{
		if (x == game->mlx.width / 2)
			game->wall.central = 1;
		set_data(game, &game->wall, &game->mlx, x);
		check_distance(game, &game->wall, game->map, x);
		game->wall.wall_x = ft_double(game->wall.side
				== 0, game->mlx.pos_y + game->wall.w_dist
				* game->wall.ray_dy, game->mlx.pos_x
				+ game->wall.w_dist * game->wall.ray_dx);
		game->wall.wall_x -= floor((game->wall.wall_x));
		game->wall.tex_x = (int)(game->wall.wall_x * (double)TEXWIDTH);
		if (game->wall.side == 0 && game->wall.ray_dx > 0)
			game->wall.tex_x = TEXWIDTH - game->wall.tex_x - 1;
		if (game->wall.side == 1 && game->wall.ray_dy < 0)
			game->wall.tex_x = TEXWIDTH - game->wall.tex_x - 1;
		game->wall.step = 1.0 * TEXHEIGHT / game->wall.line_height;
		game->wall.tex_pos = (game->wall.draw_start - game->mlx.height / 2
				+ game->wall.line_height / 2) * game->wall.step;
		render_y(game, &game->mlx, x);
		x++;
	}
}

void	check_hit(t_game *game, t_walls *data, char **map)
{
	if (data->side_dist_x < data->side_dist_y)
	{
		data->side_dist_x += data->delta_x;
		data->mx += data->step_x;
		data->side = 0;
	}
	else
	{
		data->side_dist_y += data->delta_y;
		data->my += data->step_y;
		data->side = 1;
	}
	data->hit = map[data->my][data->mx] == '1';
	hit_position(game, map);
}

void	render_y(t_game	*game, t_mlx *mlx, int x)
{
	int				y;
	t_walls			*data;

	data = &game->wall;
	y = data->draw_start;
	while (y < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (TEXHEIGHT - 1);
		data->tex_pos += data->step;
		if (data->hit == 1)
			print_wall(game, data, x, y);
		else if (data->hit == 2 && ((data->side == 0 && data->ray_dx > 0)
				|| (data->side == 1 && data->ray_dy < 0)))
			my_mlx_pixel_put(&mlx->img, game->mlx.width - x, y,
				get_pixel(&mlx->door, (data->tex_x + (int)
						(game->doors[game->wall.my][game->wall.mx].open
							* TEXWIDTH)) % TEXWIDTH, data->tex_y));
		else if (data->hit == 2)
			my_mlx_pixel_put(&mlx->img, game->mlx.width - x, y,
				get_pixel(&mlx->door, (int)(data->tex_x + ((1
								- game->doors[game->wall.my]
							[game->wall.mx].open)
							* TEXWIDTH)) % TEXWIDTH, data->tex_y));
		y++;
	}
}

void	print_wall(t_game *game, t_walls *data, int x, int y)
{
	if (data->side != 0 && data->step_y == -1)
		my_mlx_pixel_put(&game->mlx.img, game->mlx.width - x, y,
			get_pixel(&game->mlx.no, data->tex_x, data->tex_y));
	else if (data->side != 0 && data->step_y == 1)
		my_mlx_pixel_put(&game->mlx.img, game->mlx.width - x, y,
			get_pixel(&game->mlx.so, data->tex_x, data->tex_y));
	else if (data->step_x == -1)
		my_mlx_pixel_put(&game->mlx.img, game->mlx.width - x, y,
			get_pixel(&game->mlx.we, data->tex_x, data->tex_y));
	else if (data->step_x == 1)
		my_mlx_pixel_put(&game->mlx.img, game->mlx.width - x, y,
			get_pixel(&game->mlx.ea, data->tex_x, data->tex_y));
}
