/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:08:21 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/07 22:14:47 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_all(t_game *game)
{
	if (game->state.has_changed)
	{
		mlx_clear_window(game->mlx, game->win);
		draw_bgn((t_bgn){game->map->cols * TILE_SIZE, game->map->rows
			* TILE_SIZE, (game->map->cols * TILE_SIZE) * (game->map->rows
				* TILE_SIZE), 0x000000}, game);
		load_textures(game);
		update_player_animation(game, game->player);
		draw_sprite(game, game->goombas[0]);
		game->state.has_changed = false;
	}
	return (0);
}

void	load_textures(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (game->map->grid[i][j] != '\0' && game->map->grid[i][j] != '\n')
		{
			if (game->map->grid[i][j] == COIN)
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->coin->xpm, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->grid[i][j] == WALL)
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->wall->xpm, j * TILE_SIZE, i * TILE_SIZE);
			if (game->map->grid[i][j] == EXIT && game->map->coin_count < 1)
				mlx_put_image_to_window(game->mlx, game->win,
					game->map->exit->xpm, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}
