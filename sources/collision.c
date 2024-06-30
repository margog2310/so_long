/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:17:29 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/30 21:43:37 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

bool	check_collision(int keysym, t_game *game)
{
	t_point	current;
	bool	**obstacles;

	current = game->player->position;
	obstacles = find_obstacles(game->map);
	if (keysym == W && current.y > 0)
		return (obstacles[current.y - 1][current.x]);
	else if (keysym == S && current.y < game->map->rows - 1)
		return (obstacles[current.y + 1][current.x]);
	else if (keysym == A && current.x > 0)
		return (obstacles[current.y][current.x - 1]);
	else if (keysym == D && current.x < game->map->cols - 1)
		return (obstacles[current.y][current.x + 1]);
	return (false);
}
bool    check_collision_moving_objects(int keysym, t_sprite *sprite)
{
    t_point current;
    t_point next;

    
}