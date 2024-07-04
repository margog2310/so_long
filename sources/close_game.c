/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:59:23 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/04 18:06:11 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*free_images(t_img *img)
{
	if (img->xpm)
		mlx_destroy_image(img->mlx, img->xpm);
	free(img);
	img = NULL;
	return (NULL);
}

void	destroy_map(t_map *map)
{
	if (map)
	{
		if (map->grid)
			free_grid(map->grid, map->rows);
		if (map->coin)
			free_images(map->coin);
		if (map->wall)
			free_images(map->wall);
		if (map->exit)
			free_images(map->exit);
		free(map);
	}
}

// destroy a texture
void	*destroy_texture(t_img *texture)
{
	if (texture->xpm)
		mlx_destroy_image(texture->mlx, texture->xpm);
	free(texture);
	return (NULL);
}

void	handle_error(t_game *game)
{
	ft_printf("Error\n");
	if (game)
		close_window(game);
}
int	close_window(t_game *game)
{
	if (game)
	{
		if (game->map)
			destroy_map(game->map);
		if (game->img)
			ft_lstclear(&game->img, (void *)free_images);
		if (game->player)
		{
			free_images(game->player->texture);
			free(game->player);
		}
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
