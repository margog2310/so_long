/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:07 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/07 22:53:11 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	return (game);
}

// move new_image and other related stuff into this function
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

/*my_mlx_pixel_put(&img, 1280, 900, 0x00FF0000); //buffer pixels to img
mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
img.img = mlx_new_image(mlx, 1280, 900); //image buffer to hold pixels
img.addr = mlx_get_game_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	//retrieves memory addr to push pixels to*/