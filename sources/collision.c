/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:17:29 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:07:34 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// checks bounding box
bool	check_bounds(t_bounds object, t_bounds obstacle)
{
	return (object.x < obstacle.x + obstacle.w && object.x
		+ object.w > obstacle.x && object.y < obstacle.y + obstacle.h
		&& object.y + object.h > obstacle.y);
}

// creates bounding box of a sprite
t_bounds	sprite_bounds(t_sprite *sprite, t_point next)
{
	t_bounds	sprite_bounds;

	sprite_bounds.x = sprite->position.x + next.x;
	sprite_bounds.y = sprite->position.y + next.y;
	sprite_bounds.w = TILE_SIZE;
	sprite_bounds.h = TILE_SIZE;
	return (sprite_bounds);
}

// checks collision between sprite and walls
bool	check_wall_collision(t_game *game, t_bounds sprite)
{
	t_point		position;
	t_bounds	obstacle;

	position.y = 0;
	while (position.y < game->map->rows)
	{
		position.x = 0;
		while (position.x < game->map->cols)
		{
			if (game->map->grid[position.y][position.x] == WALL)
			{
				obstacle = (t_bounds){position.x * TILE_SIZE, position.y
					* TILE_SIZE, TILE_SIZE, TILE_SIZE};
				if (check_bounds(sprite, obstacle))
					return (true);
			}
			position.x++;
		}
		position.y++;
	}
	return (false);
}

// manages coin collection by player
void	collect_coins(t_game *game, t_bounds player)
{
	t_point		position;
	t_bounds	coin;

	position.y = 0;
	while (position.y < game->map->rows)
	{
		position.x = 0;
		while (position.x < game->map->cols)
		{
			if (game->map->grid[position.y][position.x] == COIN)
			{
				coin = (t_bounds){position.x * TILE_SIZE, position.y
					* TILE_SIZE, TILE_SIZE, TILE_SIZE};
				if (check_bounds(player, coin))
				{
					remove_coin(game->map, (t_point){position.x * TILE_SIZE,
						position.y * TILE_SIZE});
					game->map->grid[position.y][position.x] = SPACE;
					game->map->coin_count--;
				}
			}
			position.x++;
		}
		position.y++;
	}
}

// spawns exit if winning condition is met
bool	has_won(t_game *game, t_bounds player)
{
	t_point		position;
	t_bounds	exit;

	if (game->map->coin_count >= 1)
		return (false);
	position.y = 0;
	while (position.y < game->map->rows)
	{
		position.x = 0;
		while (position.x < game->map->cols)
		{
			if (game->map->grid[position.y][position.x] == EXIT)
			{
				exit = (t_bounds){position.x * TILE_SIZE, position.y
					* TILE_SIZE, TILE_SIZE, TILE_SIZE};
				if (check_bounds(player, exit))
					return (true);
			}
			position.x++;
		}
		position.y++;
	}
	return (false);
}
