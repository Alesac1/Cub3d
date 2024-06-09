/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error\nc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:14:53 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:14:53 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	print_error(char *str, t_game *game, int i)
{
	ft_putstr_fd (str, 2);
	close_all (game, i);
	return (0);
}

void	invalid_map_error(t_game *game, char *line, int fd)
{
	free (line);
	get_next_line(-fd);
	print_error ("Error\n Invalid Map!\n", game, 3);
}
