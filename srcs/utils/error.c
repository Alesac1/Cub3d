/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:09:35 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/27 14:09:35 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	print_error(char *str, t_game *game, int i)
{
	ft_putstr_fd (str, 2);
	if (i == 6)
		click_x(game);
	else
		close_all (game, i);
	return (0);
}

void	invalid_map_error(t_game *game, char *line, int fd)
{
	free (line);
	get_next_line(-fd);
	print_error ("Error\n Invalid Map!\n", game, 3);
}
