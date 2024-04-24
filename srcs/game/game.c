/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asacchin <asacchin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:52:57 by asacchin          #+#    #+#             */
/*   Updated: 2024/04/02 19:52:57 by asacchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


int	mouse_position(int x, int y, void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	printf("x: %d, y: %d\n", x, y);
	write(1, "mouse_position\n", 15);
	printf("width: %d\n", game->mlx.width / 2);
	if (x < game->mlx.width / 2 + game->mlx.width / 10 && x > game->mlx.width / 2 - game->mlx.width / 10)
	{
		game->moves.rot_speed = 0;
		game->moves.r = 0;
		game->moves.l = 0;
	}
	if (x > game->mlx.width / 2 + game->mlx.width / 10)
	{
		printf("right\n");
		game->moves.rot_speed = 0.005;
		game->moves.r = 1;
	}
	else if (x < game->mlx.width / 2 - game->mlx.width / 10)
	{
		printf("left\n");
		game->moves.rot_speed = -0.005;
		game->moves.l = 1;
	}
	if (x > game->mlx.width / 1.2 || x < game->mlx.width - (game->mlx.width / 1.2))
	{
		printf("   MOVE \n");
		//mlx_mouse_move(game->mlx.window, game->mlx.width / 2, game->mlx.height / 2);
	}
//	if (x > game->mlx.width / 1.2)
//	{
//	//	game->mouse_x = game->mlx.width / 2;
//	//	x = game->mlx.width / 2;
//	}
//	else if (x < game->mlx.width - (game->mlx.width / 1.2))
//	{
//	//	game->mouse_x = game->mlx.width / 2;
//	//	x = game->mlx.width / 2;
//	}
	printf("FINE \n");
	return (0);
}

void	start_game(t_game *game)
{
	mlx_hook(game->mlx.window, 17, 0, &click_x, game);
	mlx_loop_hook(game->mlx.mlx, &game_loop, game);
	mlx_hook(game->mlx.window, 6, 1L << 6, &mouse_position, game);
	mlx_hook(game->mlx.window, 3, 1L << 1, &handle_keyrelease, game);
	mlx_hook(game->mlx.window, 2, 1L << 0, &handle_keypress, game);
	mlx_loop(game->mlx.mlx);
}

int	game_loop(t_game *game, t_walls *data)
{
	animation(game);
	mlx_hook(game->mlx.window, 6, (1L << 6), mouse_position, game);
	if (game->moves.w == 1 || game->moves.s == 1)
		move_forward(game);
	if (game->moves.a == 1 || game->moves.d == 1)
		move_side(game);
	if (game->moves.l == 1 || game->moves.r == 1)
		rotate_camera(game);
	render_things(game);
	return (0);
}

void	render_things(t_game *game)
{
	render_floor_ceiling(game);
	render_walls(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.window, game->mlx.img.img, 0, 0);
}
