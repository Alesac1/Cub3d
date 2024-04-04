/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:40:31 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:40:31 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	ft_double(int b, double t, double f)
{
	if (b)
		return (t);
	return (f);
}

void	close_all(t_game *game, int r)
{
	int	i;

	if (r == 0)
		exit(0);
	free(game->path.north);
	free(game->path.east);
	free(game->path.south);
	free(game->path.west);
	free(game->path.cealing);
	free(game->path.floor);
	free(game->path.file_name);
	if (r != 3)
		exit(0);
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(0);
}
