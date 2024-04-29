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
			my_mlx_pixel_put(game, &game->mlx.img, game->mlx.width - x,
				y, game->floor_color.hex);
			my_mlx_pixel_put(game, &game->mlx.img, game->mlx.width - x,
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
			game->walls_data.central = 1;
		set_data(game, &game->walls_data, &game->mlx, x);
		check_distance(game, &game->walls_data, game->map, x);
		game->walls_data.wall_x = ft_double(game->walls_data.side
				== 0, game->mlx.pos_y + game->walls_data.w_dist
				* game->walls_data.ray_dir_y, game->mlx.pos_x
				+ game->walls_data.w_dist * game->walls_data.ray_dir_x);
		game->walls_data.wall_x -= floor((game->walls_data.wall_x));
		game->walls_data.tex_x = (int)(game->walls_data.wall_x * (double)TEXWIDTH);
		if (game->walls_data.side == 0 && game->walls_data.ray_dir_x > 0)
			game->walls_data.tex_x = TEXWIDTH - game->walls_data.tex_x - 1;
		if (game->walls_data.side == 1 && game->walls_data.ray_dir_y < 0)
			game->walls_data.tex_x = TEXWIDTH - game->walls_data.tex_x - 1;
		game->walls_data.step = 1.0 * TEXHEIGHT / game->walls_data.line_height;
		game->walls_data.tex_pos = (game->walls_data.draw_start - game->mlx.height / 2
				+ game->walls_data.line_height / 2) * game->walls_data.step;
		render_y(game, &game->mlx, x);
		x++;
	}
}

void	set_data(t_game *game, t_walls *data, t_mlx *mlx, int x)
{
	data->camera_x = 2 * x / (double)game->mlx.width - 1;
	data->ray_dir_x = mlx->dir_x + mlx->plane_x * data->camera_x;
	data->ray_dir_y = mlx->dir_y + mlx->plane_y * data->camera_x;
	data->map_x = (int)mlx->pos_x;
	data->map_y = (int)mlx->pos_y;
	data->hit = 0;
	data->delta_x = ft_double(data->ray_dir_x == 0, 1e30, fabs(1 / data->ray_dir_x));
	data->delta_y = ft_double(data->ray_dir_y == 0, 1e30, fabs(1 / data->ray_dir_y));
	data->step_x = ft_double(data->ray_dir_x < 0, -1, 1);
	data->side_dist_x = ft_double(data->ray_dir_x < 0, (mlx->pos_x - data->map_x)
			* data->delta_x, (data->map_x + 1.0 - mlx->pos_x)
			* data->delta_x);
	data->step_y = ft_double(data->ray_dir_y < 0, -1, 1);
	data->side_dist_y = ft_double(data->ray_dir_y < 0, (mlx->pos_y - data->map_y)
			* data->delta_y, (data->map_y + 1.0 - mlx->pos_y)
			* data->delta_y);
}

void	check_distance(t_game *game, t_walls *data, char **map, int x)
{
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		data->hit = map[data->map_y][data->map_x] == '1';
		check_doors(game, map);
	}
	if (game->walls_data.central == 1)
	{
		game->walls_data.c_x = game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_x;
		game->walls_data.c_y = game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_y;
		game->walls_data.c_side = game->doors[game->walls_data.map_y][game->walls_data.map_x].side;
		game->walls_data.central = 0;
		// printf("hit_x: %f  hit_y: %f  side: %d\n", game->walls_data.c_x, game->walls_data.c_y, game->walls_data.c_side);
	}
	data->w_dist = ft_double(data->side == 0, data->side_dist_x - data->delta_x,
			data->side_dist_y - data->delta_y);
	data->line_height = (int)(game->mlx.height / data->w_dist);
	data->draw_start = -data->line_height / 2 + game->mlx.height / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + game->mlx.height / 2;
	if (data->draw_end >= game->mlx.height)
		data->draw_end = game->mlx.height - 1;
}

void	render_y(t_game	*game, t_mlx *mlx, int x)
{
	int				y;
	t_walls			*data;

	data = &game->walls_data;
	y = data->draw_start;
	while (y < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (TEXHEIGHT - 1);
		data->tex_pos += data->step;
		if (data->hit == 1)
		{
			if (data->side != 0 && data->step_y == -1)
				my_mlx_pixel_put(game, &mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->no, data->tex_x, data->tex_y));
			else if (data->side != 0 && data->step_y == 1)
				my_mlx_pixel_put(game, &mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->so, data->tex_x, data->tex_y));
			else if (data->step_x == -1)
				my_mlx_pixel_put(game, &mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->we, data->tex_x, data->tex_y));
			else if (data->step_x == 1)
				my_mlx_pixel_put(game, &mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->ea, data->tex_x, data->tex_y));
		}
		else if (data->hit == 2 && ((data->side == 0 && data->ray_dir_x > 0) || (data->side == 1 && data->ray_dir_y < 0)))
			my_mlx_pixel_put(game, &mlx->img, game->mlx.width - x, y,
				get_pixel(&mlx->door, (data->tex_x + (int)(game->doors[game->walls_data.map_y][game->walls_data.map_x].open
							* TEXWIDTH)) % TEXWIDTH, data->tex_y));
		else if (data->hit == 2)
			my_mlx_pixel_put(game, &mlx->img, game->mlx.width - x, y,
				get_pixel(&mlx->door, (int)(data->tex_x + ((1 - game->doors[game->walls_data.map_y][game->walls_data.map_x].open)
							* TEXWIDTH)) % TEXWIDTH, data->tex_y));
		y++;
	}
}

void	check_doors(t_game *game, char **map)
{
	float	hit_pos;

	game->doors[game->walls_data.map_y][game->walls_data.map_x].side = game->walls_data.side;
	if (game->walls_data.side == 1)
	{
		game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_x = game->mlx.pos_x + ((game->walls_data.map_y - game->mlx.pos_y
					+ (1 - game->walls_data.step_y) / 2) / game->walls_data.ray_dir_y) * game->walls_data.ray_dir_x;
		game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_y = game->walls_data.map_y;
	}
	else
	{
		game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_x = game->walls_data.map_x;
		game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_y = game->mlx.pos_y + ((game->walls_data.map_x - game->mlx.pos_x
					+ (1 - game->walls_data.step_x) / 2) / game->walls_data.ray_dir_x) * game->walls_data.ray_dir_y;
	}
	// game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_x = game->mlx.pos_x + ((game->walls_data.map_y - game->mlx.pos_y
	// 	+ (1 - game->walls_data.step_y) / 2) / game->walls_data.ray_dir_y) * game->walls_data.ray_dir_x;
	// game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_y = game->mlx.pos_y + ((game->walls_data.map_x - game->mlx.pos_x
	// 	+ (1 - game->walls_data.step_x) / 2) / game->walls_data.ray_dir_x) * game->walls_data.ray_dir_y;
	hit_pos = ft_double(game->walls_data.side == 1, game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_x - floor(game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_x), 
				game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_y - floor(game->doors[game->walls_data.map_y][game->walls_data.map_x].hit_y));
	if (map[game->walls_data.map_y][game->walls_data.map_x] != '2')
		return ;
	game->walls_data.hit = ft_double(hit_pos <= game->doors[game->walls_data.map_y][game->walls_data.map_x].open, 2, 0);
	// printf("hit: %d   hit_pos: %f     open: %f  hit_x: %f  hit_y: %f\n", game->walls_data.hit, hit_pos, game->walls_data.doors.open, game->walls_data.doors.hit_x, game->walls_data.doors.hit_y);
}
