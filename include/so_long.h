/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:16:55 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/24 01:26:22 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define TILE_W 32
# define TILE_H 32

# define W 119
# define A 97
# define S 115
# define D 100

# define SPACE 0
# define WALL 1
# define COIN 'C'
# define EXIT 'E'
# define START 'P'

# define MARIO "./assets/small-mario.xpm"

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
// enemy struct
// player struct
// coin struct ???
// all of them should be included in t_game and potentially in t_map ??
// then you use mlx_put_img_to_win with those coordinates
typedef struct s_map
{
	char	space;
	char	coin;
	char	wall;
	char	exit;
	char	start;
	char	**grid;
	int		x;
	int		y;
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
	t_list	*maps;
	t_list	*sprites;
}			t_game;

// utils

// window
t_img		*new_image(t_game *game);
t_game		*new_window(int w, int h, char *str);
void		draw_bgn(t_bgn bgn, t_game *game);
void		*free_images(t_img *img);
int			close_window(t_game *game);
void		put_pixel_img(t_game *data, int x, int y, int colour);
// keys
int			mouse_event(int button, int x, int y, void *param);
int			on_keypress(int keysym, t_game *img);
// maps
int			open_file(char *path);
int			free_file(char *buffer);
int			close_file(int fd);
// sprites
t_img		*create_sprite(t_game *game, char *asset_path);
t_img		*load_sprites(t_game *game);
void		*destroy_sprite(t_img *sprite);
// colours
int			gen_trgb(int opacity, int red, int green, int blue);
int			get_opacity(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

#endif