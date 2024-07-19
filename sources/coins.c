/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:35:32 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:05:22 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

// load coin textures
void	initialise_coin_textures(t_game *game)
{
	game->map->coin_animations = malloc(sizeof(t_animation));
	game->map->coin_animations->frame_count = 6;
	game->map->coin_animations->frames = malloc(6 * sizeof(t_img));
	game->map->coin_animations->frames[0] = create_texture(game, COIN_ANIM1);
	game->map->coin_animations->frames[1] = create_texture(game, COIN_ANIM2);
	game->map->coin_animations->frames[2] = create_texture(game, COIN_ANIM3);
	game->map->coin_animations->frames[3] = create_texture(game, COIN_ANIM4);
	game->map->coin_animations->frames[4] = create_texture(game, COIN_ANIM5);
	game->map->coin_animations->frames[5] = create_texture(game, COIN_ANIM6);
	game->map->coin_animations->current_frame = 0;
}

// creates a new member of coin struct
t_coin	*create_coin(t_coin *coin, int x, int y)
{
	coin = malloc(sizeof(t_coin));
	coin->position.x = x;
	coin->position.y = y;
	coin->last_frame_time = 0;
	coin->delay = COIN_DELAY;
	return (coin);
}

// places coin on the game map
void	place_coin(t_map *map, int i, int j)
{
	map->coins = ft_realloc_sl(map->coins, map->coin_index * sizeof(t_coin),
			(map->coin_index + 1) * sizeof(t_coin));
	map->coins[map->coin_index] = create_coin(map->coins[map->coin_index], j
			* TILE_SIZE, i * TILE_SIZE);
	map->coins[map->coin_index]->animations = map->coin_animations;
	map->coin_index++;
}

// iterates over map and locates coin positions
void	initialise_coins(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->map->coin_index = 0;
	initialise_coin_textures(game);
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->grid[i][j])
		{
			if (game->map->grid[i][j] == COIN)
				place_coin(game->map, i, j);
			j++;
		}
		i++;
	}
}

// removes coin from map after being collected
void	remove_coin(t_map *map, t_point position)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->coin_count)
	{
		if (map->coins[i]->position.x == position.x
			&& map->coins[i]->position.y == position.y)
		{
			j = i;
			free(map->coins[i]);
			while (j < map->coin_count)
			{
				map->coins[j] = map->coins[j + 1];
				j++;
			}
			map->coins[map->coin_count - 1] = NULL;
			break ;
		}
		i++;
	}
}
