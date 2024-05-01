/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:47:50 by dde-giov          #+#    #+#             */
/*   Updated: 2024/05/01 23:48:30 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		check_hit(game, data, map);
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

void	hit_position(t_game *game, char **map)
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
