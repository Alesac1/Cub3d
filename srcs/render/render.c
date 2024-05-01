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

void	set_data(t_game *game, t_walls *data, t_mlx *mlx, int x)
{
	data->camera_x = 2 * x / (double)game->mlx.width - 1;
	data->ray_dx = mlx->dir_x + mlx->plane_x * data->camera_x;
	data->ray_dy = mlx->dir_y + mlx->plane_y * data->camera_x;
	data->mx = (int)mlx->pos_x;
	data->my = (int)mlx->pos_y;
	data->hit = 0;
	data->delta_x = ft_double(data->ray_dx == 0, 1e30, fabs(1 / data->ray_dx));
	data->delta_y = ft_double(data->ray_dy == 0, 1e30, fabs(1 / data->ray_dy));
	data->step_x = ft_double(data->ray_dx < 0, -1, 1);
	data->side_dist_x = ft_double(data->ray_dx < 0, (mlx->pos_x - data->mx)
			* data->delta_x, (data->mx + 1.0 - mlx->pos_x)
			* data->delta_x);
	data->step_y = ft_double(data->ray_dy < 0, -1, 1);
	data->side_dist_y = ft_double(data->ray_dy < 0, (mlx->pos_y - data->my)
			* data->delta_y, (data->my + 1.0 - mlx->pos_y)
			* data->delta_y);
}

void	check_distance(t_game *game, t_walls *data, char **map, int x)
{
	while (data->hit == 0)
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
		check_doors(game, map);
	}
	if (game->wall.central == 1)
	{
		game->wall.c_x = game->doors[game->wall.my][game->wall.mx].hit_x;
		game->wall.c_y = game->doors[game->wall.my][game->wall.mx].hit_y;
		game->wall.c_s = game->doors[game->wall.my][game->wall.mx].side;
		game->wall.central = 0;
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

	data = &game->wall;
	y = data->draw_start;
	while (y < data->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (TEXHEIGHT - 1);
		data->tex_pos += data->step;
		if (data->hit == 1)
		{
			if (data->side != 0 && data->step_y == -1)
				my_mlx_pixel_put(&mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->no, data->tex_x, data->tex_y));
			else if (data->side != 0 && data->step_y == 1)
				my_mlx_pixel_put(&mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->so, data->tex_x, data->tex_y));
			else if (data->step_x == -1)
				my_mlx_pixel_put(&mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->we, data->tex_x, data->tex_y));
			else if (data->step_x == 1)
				my_mlx_pixel_put(&mlx->img, game->mlx.width - x, y,
					get_pixel(&mlx->ea, data->tex_x, data->tex_y));
		}
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

void	check_doors(t_game *game, char **map)
{
	float	hit_pos;
	int		wy;
	int		wx;

	wy = game->wall.my;
	wx = game->wall.mx;
	game->doors[wy][wx].side = game->wall.side;
	game->doors[wy][wx].hit_y = wy;
	game->doors[wy][wx].hit_x = wx;
	if (game->wall.side == 1)
		game->doors[wy][wx].hit_x = game->mlx.pos_x + (
				(wy - game->mlx.pos_y + (1 - game->wall.step_y)
					/ 2) / game->wall.ray_dy) * game->wall.ray_dx;
	else
		game->doors[wy][wx].hit_y = game->mlx.pos_y + (
				(wx - game->mlx.pos_x + (1 - game->wall.step_x) / 2)
				/ game->wall.ray_dx) * game->wall.ray_dy;
	hit_pos = ft_double(game->wall.side == 1, game->doors[wy][wx].hit_x
			- floor(game->doors[wy][wx].hit_x), game->doors[wy][wx].hit_y
			- floor(game->doors[wy][wx].hit_y));
	if (map[wy][wx] != '2')
		return ;
	game->wall.hit = ft_double(hit_pos <= game->doors[wy][wx].open, 2, 0);
}
