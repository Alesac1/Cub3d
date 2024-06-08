/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:17:44 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:17:44 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	realloc_map(t_game *game)
{
	int	i;
	int	r;

	i = -1;
	while (++i > -1 && game->map[i])
	{
		r = ft_strlen(game->map[i]);
		if (r > game->p.width)
			game->p.width = (r);
	}
	i = 0;
	while (game->map[i])
	{
		game->map[i] = realloc_line(game->map[i], game->p.width);
		i++;
	}
}

char	*realloc_line(char *line, int width)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = malloc(sizeof(char) * (width + 1));
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	while (i < width)
		new_line[i++] = ' ';
	new_line[i] = '\0';
	return (new_line);
}

char	*alloc_mtx(t_game *game, char *line, int *fd, int *map_counter)
{
	int	z;

	z = 0;
	while (line)
	{
		if (line)
			free(line);
		line = get_next_line(*fd);
		game->p.height++;
	}
	close(*fd);
	game->map = malloc(sizeof(char *) * (game->p.height + 1));
	game->map[game->p.height] = '\0';
	*fd = open (game->p.file_name, O_RDONLY);
	while (*map_counter > 0)
	{
		line = next_line(&line, fd, &z);
		(*map_counter)--;
	}
	return (line);
}

int	check_colors(t_game *game, char *color, t_rgb *colors)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = ft_split(color, ',');
	while (rgb[i])
		i++;
	if (i != 3)
	{
		while (--i >= 0)
			free(rgb[i]);
		free(rgb);
		return (0);
	}
	colors->r = ft_atoi(rgb[0]);
	colors->g = ft_atoi(rgb[1]);
	colors->b = ft_atoi(rgb[2]);
	if (colors->r < 0 || colors->r > 255 || colors->g < 0
		|| colors->g > 255 || colors->b < 0 || colors->b > 255)
		i = 0;
	colors->hex = colors->r;
	colors->hex = (colors->hex << 8) + colors->g;
	colors->hex = (colors->hex << 8) + colors->b;
	free_rgb(rgb);
	return (i);
}
