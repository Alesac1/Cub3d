/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:50:36 by dde-giov          #+#    #+#             */
/*   Updated: 2024/05/06 16:27:22 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include "mlx_linux/mlx.h"
# include <sys/time.h>
# include <math.h>
# include <X11/Xlib.h>
// # include <X11/keysym.h>
// # include <X11/X.h>

# define DEFAULT 0
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define WIDTH 256
# define HEIGHT 256

# define XK_W 119
# define XK_A 97
# define XK_S 115
# define XK_D 100
# define XK_LEFT 65361
# define XK_RIGHT 65363
# define XK_UP 65362
# define XK_DOWN 65364

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
	int				hex;
}					t_rgb;

typedef struct s_map
{
	char			*n;
	char			*s;
	char			*e;
	char			*w;
	char			*cealing;
	char			*floor;
	int				height;
	int				width;
	char			*file_name;
	int				allocated;
	int				mmap_alloc;
}					t_map;

typedef struct s_spawn
{
	char	direction;
	int		x;
	int		y;
}				t_spawn;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}				t_img;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	int				width;
	int				height;
	t_img			img;
	t_img			ea;
	t_img			so;
	t_img			we;
	t_img			no;
	t_img			door;
	int				endian;
	int				old_mouse_x;
	struct timeval	start;
	long			timestamp;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			time;
	double			old_time;
	int				init_w;
	int				init_h;
}	t_mlx;

typedef struct s_obj
{
	int				door;
	float			hit_x;
	float			hit_y;
	float			open;
	int				side;
	int				direction;
}	t_obj;

typedef struct s_walls
{
	double	camera_x;
	double	ray_dx;
	double	ray_dy;
	int		mx;
	int		my;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	double	w_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		central;
	float	c_x;
	float	c_y;
	int		c_s;
}	t_walls;

typedef struct s_moves
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				l;
	int				r;
	double			move_speed;
	double			move_side_speed;
	double			rot_speed;
	int				open_all;
}	t_moves;

typedef struct s_mmap
{
	t_img			mmap;
	char			**map;
	int				width;
	int				size;
	int				sprite_size;
	int				x;
	int				y;
}					t_mmap;

typedef struct s_game
{
	struct s_mlx	mlx;
	struct s_map	p;
	struct s_rgb	floor_color;
	struct s_rgb	ceiling_color;
	struct s_spawn	spawn;
	struct s_walls	wall;
	struct s_moves	moves;
	struct s_obj	**doors;
	struct s_mmap	mmap;
	char			**map;
}					t_game;

typedef struct s_colors
{
	struct s_rgb	floor;
	struct s_rgb	ceiling;
}					t_colors;

int					check_exts(char *map);
void				start_game(t_game *game);
void				check_args(t_game *game, int argc, const char **argv,
						int *fd);
int					click_x(t_game *game);
void				check_params(t_game *game);
void				pop_map(t_game *game, int *fd, int *map_counter);
int					check_colors(t_game *game, char *color, t_rgb *colors);
int					alloc_args(t_game *game, int *fd, int *map_counter);
int					full_check(t_game *game);
void				pop_args(char *line, t_game *game, int fd);
int					print_error(char *str, t_game *game, int i);
void				init_struct(t_game *game);
char				*next_line(char **line, int *fd, int *map_counter);
void				free_rgb(char **rgb);
char				*skip_empty_lines(t_game *game, char *line, int *fd,
						int *map_counter);
char				*alloc_mtx(t_game *game, char *line, int *fd,
						int *map_counter);
void				invalid_map_error(t_game *game, char *line);
char				*realloc_line(char *line, int width);
void				realloc_map(t_game *game);
void				check_left_right(t_game *game, char **map);
void				check_up_down(t_game *game, char **map);
void				check_borders(t_game *game, char **map, int i, int x);
void				check_map(t_game *game, char **map);
int					handle_keyrelease(int keycode, t_game *game);
int					handle_keypress(int keycode, t_game *game);
void				handle_movement(int keycode, t_game *game);
void				close_all(t_game *game, int i);
void				init_game(t_game *game);
int					game_loop(t_game *game, t_walls *data);
void				set_vars(t_game *game);
double				ft_double(int b, double t, double f);
unsigned int		get_pixel(t_img *img, int x, int y);
void				init_mlx(t_game *game);
void				hit_position(t_game *game, char **map);
void				move_forward(t_game *game);
void				move_side(t_game *game);
void				rotate_camera(t_game *game);
void				set_pos(t_game *game);
void				get_addresses(t_game *game);
void				take_spawn(t_game *game, char c, int y, int x);
void				render_things(t_game *game);
void				moving(t_game *game, float next_x, float next_y);
void				render_floor_ceiling(t_game *game);
void				render_walls(t_game *game);
void				door_matrix(t_game *game);
void				animation(t_game *game);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				check_distance(t_game *game, t_walls *data,
						char **map, int x);
void				render_y(t_game	*game, t_mlx *mlx, int x);
void				set_data(t_game *game, t_walls *data, t_mlx *mlx, int x);
void				render_minimap(t_game *game);
void				blend_pixel(t_game *game, int x, int y);
void				print_mmap(t_game *game, int x, int y);
void				create_minimap(t_game *game);
void				freemmap(t_game *game);
int					mouse_position(int x, int y, void *param);
void				black_screen(t_game *game);
void				move_release(t_game *game, int keycode);
void				mmap_assign(t_game *game, int x, int y);
void				print_wall(t_game *game, t_walls *data, int x, int y);
void				init_door(t_game *game, int i, int j);

#endif