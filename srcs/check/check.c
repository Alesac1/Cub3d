/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:08:26 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:08:26 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_exts(char *map)
{
	if (map[ft_strlen(map) - 1] == 'b' && map[ft_strlen(map) - 2] == 'u'
		&& map[ft_strlen(map) - 3] == 'c' && map[ft_strlen(map)-4] == '.')
		return (0);
	return (1);
}

void	pop_map(t_game *game, int *fd, int *map_counter)
{
	char	*line;
	int		i;

	i = 0;
	line = 0;
	line = skip_empty_lines(game, line, fd, map_counter);
	line = alloc_mtx(game, line, fd, map_counter);
	while (line)
	{
		game->map[i] = line;
		line = get_next_line(*fd);
		if (!line || line[0] == '\n')
			break ;
		i++;
	}
	if (line && line[0] == '\n')
		invalid_map_error(game, line, *fd);
	close(*fd);
}

void	check_map(t_game *game, char **map)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	realloc_map(game);
	check_left_right(game, game->map);
	check_up_down(game, game->map);
	while (map[i])
	{
		while (map[i][x])
		{
			if (map[i][x] == ' ')
				check_borders(game, game->map, i, x);
			else
				take_spawn(game, map[i][x], i, x);
			x++;
		}
		x = 0;
		i++;
	}
	if (game->spawn.direction == 'I')
		print_error("Error! missing spawn point!\n", game, 3);
}

void	check_params(t_game *game, int fd)
{
	if (!full_check(game))
	{
		get_next_line(-fd);
		print_error("Error! wrong map!\n", game, 0);
	}
	if (!check_colors(game, game->p.cealing, &game->ceiling_color)
		|| !check_colors(game, game->p.floor, &game->floor_color))
	{
		get_next_line(-fd);
		print_error("Error! Wrong color!\n", game, 0);
	}
}

char	*next_line(char **line, int *fd, int *map_counter)
{
	char	*l;

	free(*line);
	l = get_next_line(*fd);
	(*map_counter)++;
	return (l);
}
