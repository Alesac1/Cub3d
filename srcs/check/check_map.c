/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:00 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:20:00 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
void	check_right(t_game *game, char **map)
{
	int i;
	int x;

	i = 0;
	x = game->path.width;
	while (map[i])
	{
		while (map[i][x])
		{
			if (map[i][x] == ' ' && --x)
				continue;
			if (map[i][x] == '1')
				break;
			else
				print_error("Error! wrong map!\n", game, 0);
		}
		x = game->path.width;
		i++;
	}
}

void	check_left_right(t_game *game, char **map)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (map[i])
	{
		while (map[i][x])
		{
			if (map[i][x] == ' ' && ++x)
				continue;
			if (map[i][x] == '1')
				break;
			else
				print_error("Error! wrong map!\n", game, 0);
		}
		x = 0;
		i++;
	}
	check_right(game, map);
}

void	check_up_down(t_game *game, char **map)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (map[i][x])
	{
		if (i == 0 || i == game->path.height)
		{
			x = 0;
			while (map[i][x])
			{
				if (map[i][x] == ' ' || map[i][x] == '1')
					x++;
				else
					print_error("Error! wrong map!\n", game, 0);
			}
		}
		i++;
	}
}

void	check_borders(t_game *game, char **map, int i, int x)
{
	if ((i - 1) >= 0)
		if ((map[i - 1][x] != ' ' && map[i - 1][x] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((x - 1) >= 0)
		if ((map[i][x - 1] != ' ' && map[i][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i + 1) < game->path.height)
		if ((map[i + 1][x] != ' ' && map[i + 1][x] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((x + 1) < game->path.width)
		if ((map[i][x + 1] != ' ' && map[i][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i + 1) < game->path.height && (x + 1) < game->path.width)
		if ((map[i + 1][x + 1] != ' ' && map[i + 1][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i + 1) < game->path.height && (x - 1) >= 0)
		if ((map[i + 1][x - 1] != ' ' && map[i + 1][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i - 1) >= 0 && (x + 1) < game->path.width)
		if ((map[i - 1][x + 1] != ' ' && map[i - 1][x + 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
	if ((i - 1) >= 0 && (x - 1) >= 0)
		if ((map[i - 1][x - 1] != ' ' && map[i - 1][x - 1] != '1'))
			print_error("Error! Invalid map!\n", game, 0);
}

void take_spawn(t_game *game, char c, int y, int x)
{
	if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
	{
		game->spawn.direction = c;
		game->spawn.x = x;
		game->spawn.y = y;
	}
	else if (c == '1' || c == '0')
		y++;
	else
		print_error("Error! invalid map input!\n", game, 0);
}