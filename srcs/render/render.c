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

	y = SCREENHEIGHT / 2 + 1;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			my_mlx_pixel_put(&game->mlx.img, SCREENWIDTH - x,
				y, game->floor_color.hex);
			my_mlx_pixel_put(&game->mlx.img, SCREENWIDTH - x,
				SCREENHEIGHT - y - 1, game->ceiling_color.hex);
			x++;
		}
		y++;
	}
}

void	render_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		set_data(&game->walls_data, &game->mlx, x);
		check_distance(game, &game->walls_data, game->map);
		game->walls_data.wall_x = ft_double(game->walls_data.side == 0, game->mlx.pos_y + game->walls_data.w_dist
				* game->walls_data.ray_dir_y, game->mlx.pos_x + game->walls_data.w_dist * game->walls_data.ray_dir_x);
		game->walls_data.wall_x -= floor((game->walls_data.wall_x));
		game->walls_data.tex_x = (int)(game->walls_data.wall_x * (double)TEXWIDTH);
		if (game->walls_data.side == 0 && game->walls_data.ray_dir_x > 0)
			game->walls_data.tex_x = TEXWIDTH - game->walls_data.tex_x - 1;
		if (game->walls_data.side == 1 && game->walls_data.ray_dir_y < 0)
			game->walls_data.tex_x = TEXWIDTH - game->walls_data.tex_x - 1;
		game->walls_data.step = 1.0 * TEXHEIGHT / game->walls_data.line_height;
		game->walls_data.tex_pos = (game->walls_data.draw_start - SCREENHEIGHT / 2
				+ game->walls_data.line_height / 2) * game->walls_data.step;
		render_y(&game->walls_data, &game->mlx, x);
		x++;
	}
}

void	set_data(t_walls *data, t_mlx *mlx, int x)
{
	data->camera_x = 2 * x / (double)SCREENWIDTH - 1;
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

void	check_distance(t_game *game, t_walls *data, char **map)
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
	data->w_dist = ft_double(data->side == 0, data->side_dist_x - data->delta_x,
			data->side_dist_y - data->delta_y);
	data->line_height = (int)(SCREENHEIGHT / data->w_dist);
	data->draw_start = -data->line_height / 2 + SCREENHEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREENHEIGHT / 2;
	if (data->draw_end >= SCREENHEIGHT)
		data->draw_end = SCREENHEIGHT - 1;
}

void	render_y(t_walls *data, t_mlx *mlx, int x)
{
	int				y;

	y = data->draw_start;
	while (y < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (TEXHEIGHT - 1);
		data->tex_pos += data->step;
		if (data->hit == 1)
		{
			if (data->side != 0 && data->step_y == -1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->no, data->tex_x, data->tex_y));
			else if (data->side != 0 && data->step_y == 1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->so, data->tex_x, data->tex_y));
			else if (data->step_x == -1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->we, data->tex_x, data->tex_y));
			else if (data->step_x == 1)
				my_mlx_pixel_put(&mlx->img, SCREENWIDTH - x, y,
					get_pixel(&mlx->ea, data->tex_x, data->tex_y));
		}
		y++;
	}
}

void	check_doors(t_game *game, char **map)
{
	float	hit_pos;

	if (map[game->walls_data.map_y][game->walls_data.map_x] != '2')
		return ;
	if (game->walls_data.side == 0)
	{
		game->walls_data.doors.hit_x = game->mlx.pos_x + ((game->walls_data.map_y - game->mlx.pos_y
			+ (1 - game->walls_data.step_y) / 2) / game->walls_data.ray_dir_y) * game->walls_data.ray_dir_x;
		game->walls_data.doors.hit_y = game->walls_data.map_y + (1 - game->walls_data.step_y) / 2;
	}
	else
	{
		game->walls_data.doors.hit_x = game->walls_data.map_x + (1 - game->walls_data.step_x) / 2;
		game->walls_data.doors.hit_y = game->mlx.pos_y + ((game->walls_data.map_x - game->mlx.pos_x
			+ (1 - game->walls_data.step_x) / 2) / game->walls_data.ray_dir_x) * game->walls_data.ray_dir_y;
	}
	hit_pos = ft_double(game->walls_data.side == 0, game->walls_data.doors.hit_x - floor(game->walls_data.doors.hit_x), 
	game->walls_data.doors.hit_y - floor(game->walls_data.doors.hit_y));
	game->walls_data.hit = ft_double(hit_pos <= game->walls_data.doors.open, 2, 0);
}
