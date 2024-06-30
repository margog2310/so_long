/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:17:29 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/30 23:26:04 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_bounds(t_bounds object, t_bounds obstacle)
{
	return (object.x < obstacle.x + obstacle.w && object.x
		+ object.w > obstacle.x && object.y < obstacle.y + obstacle.h
		&& object.y + object.h > obstacle.y);
}

bool	**find_obstacles(t_map *map)
{
	int		i;
	int		j;
	bool	**obstacles;

	i = 0;
	obstacles = (bool **)ft_allocate_grid(map->rows, map->cols, sizeof(bool));
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j] != '\n' && map->grid[i][j] != '\0')
		{
			if (map->grid[i][j] == WALL)
				obstacles[i][j] = true;
			else
				obstacles[i][j] = false;
			j++;
		}
		i++;
	}
	return (obstacles);
}

bool	check_collision(t_game *game, t_point next)
{
	t_bounds player;
	t_bounds obstacle;
	bool	**obstacles;

	player.x = game->player->position.x + next.x;
	player.y = game->player->position.y + next.y;
	player.w = TILE_SIZE;
	player.h = TILE_SIZE;
	obstacles = find_obstacles(game->map);
	// check if next position is an obstacle based on obstacles array (coordinates * tile_size)
}
// collisions for moving objects
/*bool    check_collision_moving_objects(int keysym, t_sprite *sprite)
{
	t_point current;
	t_point next;

	current = sprite->position;
	if (keysym == W && current.y > 0)
		next.y -= SPEED;
}*/