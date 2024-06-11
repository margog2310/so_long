/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:07 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/11 23:28:39 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	*new_image(t_game *game)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (close_window(game), NULL);
	img->mlx = game->mlx;
	img->xpm = mlx_new_image(game->mlx, game->w, game->h);
	if (!img->xpm)
		return (free(img), close_window(game), NULL);
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
		return (close_window(game), NULL);
	game->w = w;
	game->h = h;
	game->sprites = NULL;
	game->img = NULL;
	img = new_image(game);
	if (!img)
		return (close_window(game), NULL);
	game->addr = mlx_get_data_addr(img->xpm, &game->bpp, &game->line_len,
			&game->endian);
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

void	*free_images(t_img *img)
{
	if (img->xpm)
		mlx_destroy_image(img->mlx, img->xpm);
	free(img);
	img = NULL;
	return (NULL);
}

int	close_window(t_game *game)
{
	if (game)
	{
		if (game->sprites)
			ft_lstclear(&game->sprites, (void *)destroy_sprite);
		if (game->map)
			destroy_map(game->map);
		if (game->img)
			ft_lstclear(&game->img, (void *)free_images);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game);
	}
	exit(EXIT_SUCCESS);
}

/*my_mlx_pixel_put(&img, 1280, 900, 0x00FF0000); //buffer pixels to img
mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
img.img = mlx_new_image(mlx, 1280, 900); //image buffer to hold pixels
img.addr = mlx_get_game_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	//retrieves memory addr to push pixels to*/