/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:16:55 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/13 18:23:59 by mganchev         ###   ########.fr       */
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
	int		x;
	int		y;
}			t_point;

typedef struct s_img
{
	void	*mlx;
	void	*xpm;
	int		h;
	int		w;
}			t_img;

typedef struct s_bgn
{
	int		x;
	int		y;
	int		size;
	int		colour;
}			t_bgn;

typedef struct s_sprite
{
	t_img	*texture;
	t_point	position;
	int		direction;
}			t_sprite;

// enemy struct
// player struct
// coin struct ???
// all of them should be included in t_game and potentially in t_map ??
// then you use mlx_put_img_to_win with those coordinates
typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
	t_list	*textures;
}			t_map;

typedef struct s_game
{
	t_list	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		line_len;
	int		endian;
	bool	has_changed;
	t_map	*map;
	t_list	*sprites;
}			t_game;

// game
t_game		*create_game(char *file_path);
int			render_all(t_game *game);
// window
t_img		*new_image(t_game *game);
t_game		*new_window(int w, int h, char *str);
void		draw_bgn(t_bgn bgn, t_game *game);
void		*free_images(t_img *img);
int			close_window(t_game *game);
void		put_pixel_img(t_game *data, int x, int y, int colour);
// keys
int			move_left(int keysym, t_game *game);
int			mouse_event(int button, int x, int y, void *param);
int			on_keypress(int keysym, t_game *img);
// maps
int			open_file(char *path);
t_map		*read_file(int fd, t_map *map);
t_map		*create_game_map(char *file_path);
int			close_file(int fd);
void		free_grid(char **grid, int line_count);
bool		check_line_len(char **grid, int line_count);
bool		check_map_symbols(char **grid, int line_count);
bool		check_repeat(char **grid, int line_count);
bool		check_borders(char **grid, int line_count);
bool		check_if_boxed(char **grid, int line_count);
bool		check_map_errors(char **grid, int line_count);
void		destroy_map(t_map *map);
// textures
t_img		*create_texture(t_game *game, char *asset_path, int x, int y);
void		load_textures(t_game *game);
void		*destroy_texture(t_img *texture);
// path finding
bool		is_valid(char **grid, bool **visited, int row, int col,
				int line_count);
void		depth_first_search(char **grid, bool **visited, t_point current,
				int *coins, int line_count);
bool		is_path(char **grid, t_point start, t_point end, int *coins,
				int line_count);
bool		find_path(char **grid, int line_count);
// sprites
t_sprite	*create_sprite(t_game *game, char *asset_path, int x, int y);
void		*destroy_sprite(t_sprite *sprite);
// colours
int			gen_trgb(int opacity, int red, int green, int blue);
int			get_opacity(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
// misc
char		get_char(char **grid, int line_count, int x, int y);
void		*ft_realloc_sl(void *ptr, size_t old_size, size_t new_size);

#endif