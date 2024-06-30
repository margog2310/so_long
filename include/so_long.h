/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:16:55 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/30 22:27:02 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define TILE_SIZE 32
# define SPEED 8

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define SPACE '0'
# define WALL '1'
# define COIN 'C'
# define EXIT 'E'
# define START 'P'
# define MONSTER 'M'

// sprites
# define MARIO "./assets/small-mario.xpm"
# define ENEMY "./assets/goomba.xpm"
// map tiles
# define PLATFORM "./assets/block.xpm"
# define COLLECTIBLE "./assets/coin.xpm"
# define ENTER "./assets/pipe.xpm"
# define FINISH // draw castle or flag pole basically (rip)

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_bounds
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_bounds;

typedef struct s_img
{
	void		*mlx;
	void		*xpm;
	int			h;
	int			w;
}				t_img;

typedef struct s_bgn
{
	int			x;
	int			y;
	int			size;
	int			colour;
}				t_bgn;

typedef struct s_sprite
{
	t_img		*texture;
	t_point		position;
	t_point		velocity;
	int			direction;

}				t_sprite;

// enemy struct
// player struct
// coin struct ???
// all of them should be included in t_game and potentially in t_map ??
// then you use mlx_put_img_to_win with those coordinates

typedef struct s_map
{
	char		**grid;
	int			rows;
	int			cols;
	int			coins;
	t_list		*textures;
}				t_map;

typedef struct s_state
{
	bool		is_running;
	bool		has_won;
	bool		has_lost;
	bool		is_dead;
	bool		has_changed;
}				t_state;
typedef struct s_game
{
	t_list		*img;
	void		*mlx;
	void		*win;
	char		*addr;
	int			h;
	int			w;
	int			bpp;
	int			line_len;
	int			endian;
	t_state		state;
	t_map		*map;
	t_list		*sprites;
	t_sprite	*player;
}				t_game;

// game
t_game			*create_game(char *file_path);
int				game_loop(t_game *game);
int				render_all(t_game *game);
bool			game_is_running(t_game *game);
int				handle_input(int keysym, t_game *game);
// window
t_img			*new_image(t_game *game);
t_game			*new_window(int w, int h, char *str);
void			draw_bgn(t_bgn bgn, t_game *game);
void			*free_images(t_img *img);
int				close_window(t_game *game);
void			put_pixel_img(t_game *data, int x, int y, int colour);
// movement
int				move_right(t_game *game);
int				move_left(t_game *game);
int				move_up(t_game *game);
int				move_down(t_game *game);
// collisions
bool			**find_obstacles(t_map *map);
bool			check_collision(int keysym, t_game *game);
// maps
int				open_file(char *path);
t_map			*read_file(int fd, t_map *map);
t_map			*create_game_map(char *file_path);
int				close_file(int fd);
void			free_grid(char **grid, int line_count);
bool			check_line_len(t_map *map);
bool			check_map_symbols(t_map *map);
bool			check_repeat(t_map *map);
bool			check_borders(t_map *map);
bool			check_if_boxed(t_map *map);
bool			check_map_errors(t_map *map);
void			destroy_map(t_map *map);
// textures
t_img			*create_texture(t_game *game, char *asset_path, int x, int y);
void			load_textures(t_game *game);
void			*destroy_texture(t_img *texture);
// path finding
bool			is_valid(t_map *map, bool **visited, int row, int col);
void			depth_first_search(t_map *map, bool **visited, t_point current);
bool			is_path(t_map *map, t_point start, t_point end);
bool			validate_path(t_map *map, t_point start, char dest);
bool			find_path(t_map *map);
// sprites
t_sprite		*create_sprite(t_game *game, char *asset_path, int x, int y);
void			draw_sprite(t_game *game, t_sprite *sprite);
void			initialize_player(t_game *game);
// colours
int				gen_trgb(int opacity, int red, int green, int blue);
int				get_opacity(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
// misc
char			get_char(char **grid, int line_count, int x, int y);
void			*ft_realloc_sl(void *ptr, size_t old_size, size_t new_size);

#endif