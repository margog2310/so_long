/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:08:21 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/14 23:18:10 by mganchev         ###   ########.fr       */
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
		print_moves(game);
		game->state.has_changed = false;
	}
	update_enemies(game);
	update_animations(game);
	return (0);
}

void	update_game_state(t_game *game)
{
    t_bounds	player_bounds;
    int			i;
    t_sprite	*enemy;
    t_bounds	enemy_bounds;

    player_bounds = sprite_bounds(game->player, game->player->position);
    i = 0;
    while (i < game->enemy_index)
    {
        enemy = game->goombas[i];
        enemy_bounds = sprite_bounds(enemy, enemy->position);
        if (player_enemy_collision(game, player_bounds))
        {
            game->player->is_dead = true;
            game->player->is_moving = false;
            game->state.has_lost = true;
        }
        i++;
    }
}

void	update_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_index)
	{
		enemy_patrol(game, game->goombas[i]);
		i++;
	}
}

void	update_animations(t_game *game)
{
	int	i;
	int	j;

	i = j = 0;
	while (i < game->map->coin_count)
	{
		update_coin_animation(game, game->map->coins[i]);
		i++;
	}
	while (j < game->enemy_index)
	{
		update_goomba_animation(game, game->goombas[j]);
		j++;
	}
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
