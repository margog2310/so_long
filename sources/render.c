/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:08:21 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/26 21:35:17 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_all(t_game *game)
{
	t_img	*img;
	
	if (game->state.has_changed)
	{
		img = game->img->content;
		mlx_put_image_to_window(game->mlx, game->win, img->xpm, 0, 0);
		mlx_clear_window(game->mlx, game->win);
		draw_bgn((t_bgn){game->map->cols * TILE_SIZE, game->map->rows
			* TILE_SIZE, (game->map->cols * TILE_SIZE) * (game->map->rows
				* TILE_SIZE), 0x000000}, game);
		draw_sprite(game, game->player);
		load_textures(game);
		game->state.has_changed = false;
	}
	return (0);
}
void	initialize_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (game->map->grid[i][j] != '\0' && game->map->grid[i][j] != '\n')
		{
			if (get_char(game->map->grid, game->map->rows, j, i) == START)
			{
				game->player = create_sprite(game, MARIO, j * TILE_SIZE, i
						* TILE_SIZE);
				return ;
			}
			j++;
		}
		i++;
	}
}
