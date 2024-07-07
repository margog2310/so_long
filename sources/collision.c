/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:17:29 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/07 20:04:52 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_bounds(t_bounds object, t_bounds obstacle)
{
	return (object.x < obstacle.x + obstacle.w && object.x
		+ object.w > obstacle.x && object.y < obstacle.y + obstacle.h
		&& object.y + object.h > obstacle.y);
}

t_bounds	player_bounds(t_sprite *player, t_point next)
{
	t_bounds	player_bounds;

	player_bounds.x = player->position.x + next.x;
	player_bounds.y = player->position.y + next.y;
	player_bounds.w = TILE_SIZE;
	player_bounds.h = TILE_SIZE;
	return (player_bounds);
}

bool	check_wall_collision(t_game *game, t_bounds player)
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
				if (check_bounds(player, obstacle))
					return (true);
			}
			position.x++;
		}
		position.y++;
	}
	return (false);
}

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
					game->map->grid[position.y][position.x] = SPACE;
					game->map->coin_count--;
				}
			}
			position.x++;
		}
		position.y++;
	}
}

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
