/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:07 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:13:49 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// creates a new image
t_img	*new_image(t_game *game)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (handle_error(game), NULL);
	img->mlx = game->mlx;
	img->xpm = mlx_new_image(game->mlx, game->w, game->h);
	if (!img->xpm)
		return (free(img), handle_error(game), NULL);
	ft_lstadd_back(&game->img, ft_lstnew(img));
	return (img);
}

// creates a new game window
t_game	*new_window(int w, int h, char *str)
{
	t_game	*game;
	t_img	*img;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), NULL);
	game->win = mlx_new_window(game->mlx, w, h, str);
	if (!game->win)
		return (handle_error(game), NULL);
	game->w = w;
	game->h = h;
	game->img = NULL;
	img = new_image(game);
	if (!img)
		return (handle_error(game), NULL);
	game->addr = mlx_get_data_addr(img->xpm, &game->bpp, &game->line_len,
			&game->endian);
	game->move_counter = 0;
	game->goombas = NULL;
	initialise_enemy_textures(game);
	return (game);
}

// creates game background
void	draw_bgn(t_bgn bgn, t_game *game)
{
	unsigned short int	i;
	unsigned short int	j;
	t_img				*img;

	img = game->img->content;
	if (!img)
		return ;
	i = 0;
	while (i < game->h)
	{
		j = 0;
		while (j < game->w)
		{
			put_pixel_img(game, j * TILE_SIZE, i * TILE_SIZE, bgn.colour);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, img->xpm, 0, 0);
}
