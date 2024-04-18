/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:53:43 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:53:43 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_game *game)
{
    float next_x;
    float next_y;
	float player_relative_pos_x;
	float player_relative_pos_y;

    next_x = game->mlx.pos_x + game->mlx.dir_x * game->moves.move_speed;
    next_y = game->mlx.pos_y + game->mlx.dir_y * game->moves.move_speed;

    // Calcola la posizione relativa del giocatore rispetto alla porta
    player_relative_pos_x = next_x - floor(next_x);
    player_relative_pos_y = next_y - floor(next_y);

    // Controlla se la cella successiva contiene un muro o una porta chiusa
    if (game->map[(int)next_y][(int)next_x] != '1')
    {
        // Se la cella contiene una porta, verifica lo stato della porta
        if (game->map[(int)next_y][(int)next_x] == '2')
        {
            // Verifica se la porta è abbastanza aperta in base all'orientamento
            if ((game->walls_data.doors.side == 1 && player_relative_pos_x > game->walls_data.doors.open) ||
                (game->walls_data.doors.side == 0 && player_relative_pos_y > game->walls_data.doors.open))
            {
                // La porta è abbastanza aperta, permetti il passaggio
                game->mlx.pos_x = next_x;
                game->mlx.pos_y = next_y;
            }
            // Altrimenti, il giocatore non può passare attraverso la parte chiusa della porta
        }
        else
        {
            // Se la cella successiva non è né un muro né una porta, permetti il movimento
            game->mlx.pos_x = next_x;
            game->mlx.pos_y = next_y;
        }
    }
}

void	move_side(t_game *game)
{
	if (game->map[(int)(game->mlx.pos_y)]
			[(int)(game->mlx.pos_x + game->mlx.plane_x * game->moves.move_side_speed)]
				!= '1')
		game->mlx.pos_x += game->mlx.plane_x * game->moves.move_side_speed;
	if (game->map
		[(int)(game->mlx.pos_y + game->mlx.plane_y * game->moves.move_side_speed)]
		[(int)(game->mlx.pos_x)] != '1')
		game->mlx.pos_y += game->mlx.plane_y * game->moves.move_side_speed;
}

void	rotate_camera(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->mlx.dir_x;
	old_plane_x = game->mlx.plane_x;
	game->mlx.dir_x = game->mlx.dir_x * cos(game->moves.rot_speed)
		- game->mlx.dir_y * sin(game->moves.rot_speed);
	game->mlx.dir_y = old_dir_x * sin(game->moves.rot_speed)
		+ game->mlx.dir_y * cos(game->moves.rot_speed);
	game->mlx.plane_x = game->mlx.plane_x * cos(game->moves.rot_speed)
		- game->mlx.plane_y * sin(game->moves.rot_speed);
	game->mlx.plane_y = old_plane_x * sin(game->moves.rot_speed)
		+ game->mlx.plane_y * cos(game->moves.rot_speed);
}
