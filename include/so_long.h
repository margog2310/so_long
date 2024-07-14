/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:16:55 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/14 23:42:43 by mganchev         ###   ########.fr       */
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
# include <time.h>

# define TILE_SIZE 32
# define SPEED 8

# define DELAY 0.075
# define PATROL_DELAY 0.25

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
# define MARIO "./assets/mario_idle.xpm"
# define ANIM1_RIGHT "./assets/mario_run_1_right.xpm"
# define ANIM1_LEFT "./assets/mario_run_1_left.xpm"
# define ANIM2_RIGHT "./assets/mario_run_2_right.xpm"
# define ANIM2_LEFT "./assets/mario_run_2_left.xpm"
# define ANIM3_RIGHT "./assets/mario_run_3_right.xpm"
# define ANIM3_LEFT "./assets/mario_run_3_left.xpm"
# define MARIO_DEAD "./assets/mario_dead.xpm"
# define ENEMY_ANIM1 "./assets/goomba_walk_1.xpm"
# define ENEMY_ANIM2 "./assets/goomba_walk_2.xpm"
# define ENEMY_DEAD "./assets/goomba_dead.xpm"
// map tiles
# define PLATFORM "./assets/block.xpm"
# define COIN_ANIM1 "./assets/coin_1.xpm"
# define COIN_ANIM2 "./assets/coin_2.xpm"
# define COIN_ANIM3 "./assets/coin_3.xpm"
# define COIN_ANIM4 "./assets/coin_4.xpm"
# define COIN_ANIM5 "./assets/coin_5.xpm"
# define COIN_ANIM6 "./assets/coin_6.xpm"
# define FINISH "./assets/flagpole.xpm"

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

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

enum			sprite
{
	PLAYER,
	ENEMY,
	COINS,
};
typedef struct s_animation
{
	t_img		**frames;
	int			w;
	int			h;
	int			frame_count;
	int			current_frame;
	// enum sprite	sprite;
}				t_animation;

typedef struct s_coin
{
	t_animation	*animations;
	t_point		position;
}				t_coin;

typedef struct s_sprite
{
	t_animation	*animations;
	t_img		*texture;
	t_img		*dead;
	t_point		position;
	bool		is_moving;
	bool		is_dead;
	int			direction;
}				t_sprite;

typedef struct s_bounds
{
	int			x;
	int			y;
	int			w;
	int			h;
}				t_bounds;

typedef struct s_map
{
	char		**grid;
	int			rows;
	int			cols;
	int			coin_count;
	int			coin_index;
	t_coin		**coins;
	t_img		*wall;
	t_img		*exit;
}				t_map;

typedef struct s_state
{
	bool		is_running;
	bool		has_won;
	bool		has_lost;
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
	int			move_counter;
	int			enemy_index;
	char		*file_path;
	t_state		state;
	t_map		*map;
	t_sprite	*player;
	t_sprite	**goombas;
}				t_game;

// game
t_game			*create_game(char *file_path);
void			initialise_game_state(t_game *game);
void			initialise_coins(t_game *game);
int				game_loop(t_game *game);
void			update_game_state(t_game *game);
int				render_all(t_game *game);
bool			game_is_running(t_game *game);
int				handle_input(int keysym, t_game *game);
void			handle_error(t_game *game);
void			print_moves(t_game *game);
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
int				enemy_patrol(t_game *game, t_sprite *goomba);
void			update_enemies(t_game *game);
bool			player_is_moving(t_game *game);
// collisions
bool			check_bounds(t_bounds object, t_bounds obstacle);
t_bounds		sprite_bounds(t_sprite *sprite, t_point next);
bool			check_wall_collision(t_game *game, t_bounds sprite);
void			collect_coins(t_game *game, t_bounds player);
void			remove_coin(t_map *map, t_point position);
bool			has_won(t_game *game, t_bounds player);
bool			check_collision(t_game *game, t_point next);
bool			check_enemy_collision(t_game *game, t_sprite *goomba,
					t_point next);
bool			player_enemy_collision(t_game *game, t_bounds player);
// maps
int				open_file(char *path);
t_map			*read_file(int fd, t_map *map);
t_map			*create_game_map(char *file_path);
t_coin			*create_coin(t_coin *coin, int x, int y);
int				close_file(int fd);
void			free_grid(char **grid, int line_count);
bool			check_line_len(t_map *map);
bool			check_map_symbols(t_map *map);
bool			check_repeat(t_map *map);
bool			check_borders(t_map *map);
bool			check_if_boxed(t_map *map);
bool			check_map_errors(t_map *map);
void			destroy_coin(t_coin *coin);
void			destroy_map(t_map *map);
// textures
t_img			*create_texture(t_game *game, char *asset_path);
void			initialise_textures(t_game *game);
void			initialise_coin_textures(t_game *game, t_coin *coin);
void			initialise_player_textures(t_game *game);
void			initialise_enemy_textures(t_game *game, t_sprite *goomba);
void			load_textures(t_game *game);
// path finding
bool			is_valid(t_map *map, bool **visited, int row, int col);
void			depth_first_search(t_map *map, bool **visited, t_point current);
bool			is_path(t_map *map, t_point start, t_point end);
bool			validate_path(t_map *map, t_point start, char dest);
bool			find_path(t_map *map);
// sprites
t_sprite		*create_sprite(t_game *game, char *asset_path, int x, int y);
t_sprite		*create_goomba(t_game *game, t_sprite *goomba, int x, int y);
void			draw_sprite(t_game *game, t_sprite *sprite);
void			initialize_player(t_game *game);
void			initialize_enemies(t_game *game);
void			destroy_sprite(t_sprite *sprite);
void			destroy_enemies(t_game *game);
// animations
void			update_animations(t_game *game);
void			move_right_animation(t_game *game, t_sprite *player);
void			move_left_animation(t_game *game, t_sprite *player);
void			update_player_animation(t_game *game, t_sprite *player);
void			update_goomba_animation(t_game *game, t_sprite *goomba);
void			update_coin_animation(t_game *game, t_coin *coin);
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