/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checl_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:03:15 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 20:03:15 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_args(t_game *game, int argc, const char **argv, int *fd)
{
	int	map_counter;

	map_counter = 0;
	if (argc != 2 || check_exts((char *)argv[1]))
		print_error("Error! invalid or missing map!\n", game, 0);
	game->p.file_name = ft_strdup((char *)argv[1]);
	*fd = open(game->p.file_name, O_RDONLY);
	if (*fd == -1)
		print_error("Error! Wrong path!\n", game, 0);
	init_struct(game);
	if (!alloc_args(game, fd, &map_counter))
		print_error("missing map instructions!\n", game, 0);
	pop_map(game, fd, &map_counter);
	check_map(game, game->map);
	door_matrix(game);
}

int	alloc_args(t_game *game, int *fd, int *map_counter)
{
	char	*line;

	line = get_next_line(*fd);
	(*map_counter)++;
	while (line)
	{
		if (line[0] == '\n')
		{
			line = next_line(&line, fd, map_counter);
			continue ;
		}
		pop_args(line, game, *fd);
		if (full_check(game))
			break ;
		free(line);
		line = get_next_line(*fd);
		(*map_counter)++;
	}
	free(line);
	check_params(game, *fd);
	return (1);
}

void	pop_args(char *line, t_game *game, int fd)
{
	if (!ft_strncmp(line, "NO", 2) && game->p.n == DEFAULT)
		game->p.n = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, "EA", 2) && game->p.e == DEFAULT)
		game->p.e = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, "SO", 2) && game->p.s == DEFAULT)
		game->p.s = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, "WE", 2) && game->p.w == DEFAULT)
		game->p.w = ft_strtrim(line + 2, " \n");
	else if (!ft_strncmp(line, "C", 1) && game->p.cealing == DEFAULT)
		game->p.cealing = ft_strtrim(line + 1, " \n");
	else if (!ft_strncmp(line, "F", 1) && game->p.floor == DEFAULT)
		game->p.floor = ft_strtrim(line + 1, " \n");
	else
	{
		free(line);
		get_next_line(-fd);
		print_error("Wrong map!\n", game, 1);
	}
}

int	full_check(t_game *game)
{
	if (game->p.n != DEFAULT)
		if (game->p.w != DEFAULT)
			if (game->p.e != DEFAULT)
				if (game->p.s != DEFAULT)
					if (game->p.cealing != DEFAULT)
						if (game->p.floor != DEFAULT)
							return (1);
	return (0);
}

char	*skip_empty_lines(t_game *game, char *line, int *fd, int *map_counter)
{
	line = get_next_line(*fd);
	(*map_counter)++;
	while (line && line[0] == '\n')
		line = next_line(&line, fd, map_counter);
	if (!line || line[0] == '\0')
		print_error("Error! Wrong map!\n", game, 0);
	return (line);
}
