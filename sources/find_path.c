/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:19:30 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/30 20:31:07 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// checks that a cell is valid
bool	is_valid(t_map *map, bool **visited, int row, int col)
{
	int	rows;
	int	cols;

	rows = map->rows;
	cols = map->cols;
	return ((row >= 0) && (row < rows) && (col >= 0) && (col < cols)
		&& (map->grid[row][col] != WALL) && (!visited[row][col]));
}

// implements DFS algorithm + coin count
void	depth_first_search(t_map *map, bool **visited, t_point current)
{
	int	i;
	int	row_vector[4];
	int	col_vector[4];

	row_vector[0] = 0;
	row_vector[1] = 1;
	row_vector[2] = 0;
	row_vector[3] = -1;
	col_vector[0] = -1;
	col_vector[1] = 0;
	col_vector[2] = 1;
	col_vector[3] = 0;
	visited[current.y][current.x] = true;
	i = 0;
	while (i < 4)
	{
		if (is_valid(map, visited, current.y + row_vector[i], current.x
				+ col_vector[i]))
			depth_first_search(map, visited, (t_point){current.x
				+ col_vector[i], current.y + row_vector[i]});
		i++;
	}
}

// initialises DFS algorithm
bool	is_path(t_map *map, t_point start, t_point end)
{
	int		rows;
	int		cols;
	bool	**visited;

	rows = map->rows;
	cols = map->cols;
	visited = (bool **)ft_allocate_grid(rows, cols, sizeof(bool));
	depth_first_search(map, visited, start);
	if (visited[end.y][end.x])
		return (free_grid((char **)visited, rows), true);
	return (free_grid((char **)visited, rows), false);
}

// checks if coins/exit is reachable from start
bool	validate_path(t_map *map, t_point start, char dest)
{
	int i;
	int	j;
	t_point	end;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j] != '\0' && map->grid[i][j] != '\n')
		{
			if ((dest == EXIT && map->grid[i][j] == EXIT) || (dest == COIN
					&& map->grid[i][j] == COIN))
			{
				end.y = i;
				end.x = j;
				if (!is_path(map, start, end))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
// locates START and EXIT/COIN and finds a path
bool	find_path(t_map *map)
{
	int		i;
	char	*symbol;
	t_point	start;

	i = 0;
	while (i < map->rows)
	{
		symbol = ft_strchr(map->grid[i], START);
		if (symbol)
		{
			start.y = i;
			start.x = symbol - map->grid[i];
			if (!validate_path(map, start, EXIT))
				return (false);
			if (!validate_path(map, start, COIN))
				return (false);
			return (true);
		}
		i++;
	}
    return (false);
}
