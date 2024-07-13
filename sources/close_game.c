/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:59:23 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/13 02:08:57 by mganchev         ###   ########.fr       */
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
		if (map->coins)
		{
			while (--map->coin_count >= 0)
				destroy_coin(map->coins[map->coin_count]);
			free(map->coins);
		}
		if (map->grid)
			free_grid(map->grid, map->rows);
		if (map->wall)
			free_images(map->wall);
		if (map->exit)
			free_images(map->exit);
		free(map);
	}
}

void	destroy_enemies(t_game *game)
{
	if (game->goombas)
	{
		while (--game->enemy_index >= 0)
			destroy_sprite(game->goombas[game->enemy_index]);
		free(game->goombas);
	}
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
			destroy_sprite(game->player);
		if (game->goombas)
			destroy_enemies(game);
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

void	handle_error(t_game *game)
{
	ft_printf("Error\n");
	if (game)
		close_window(game);
}
