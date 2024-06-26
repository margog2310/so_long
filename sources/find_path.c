/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:19:30 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/26 22:54:56 by mganchev         ###   ########.fr       */
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
void	depth_first_search(t_map *map, bool **visited, t_point current,
		int *coins)
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
	visited[current.x][current.y] = true;
	if (map->grid[current.x][current.y] == COIN)
		(*coins)++;
	i = 0;
	while (i < 4)
	{
		if (is_valid(map, visited, current.x + row_vector[i], current.y
				+ col_vector[i]))
			depth_first_search(map, visited, (t_point){current.x
				+ row_vector[i], current.y + col_vector[i]}, coins);
		i++;
	}
}

// initialises DFS algorithm
bool	is_path(t_map *map, t_point start, t_point end, int *coins)
{
	int		rows;
	int		cols;
	bool	**visited;

	rows = map->rows;
	cols = map->cols;
	visited = (bool **)ft_allocate_grid(rows, cols, sizeof(bool));
	depth_first_search(map, visited, start, coins);
	if (visited[end.x][end.y])
		return (free_grid((char **)visited, rows), true);
	return (free_grid((char **)visited, rows), false);
}

// locates START and EXIT and finds a path
bool	find_path(t_map *map)
{
	int		i;
	int		coins;
	char	*symbol;
	t_point	start;
	t_point	end;

	i = 0;
	coins = 0;
	while (i < map->rows)
	{
		symbol = ft_strchr(map->grid[i], START);
		if (symbol)
		{
			start.x = i;
			start.y = symbol - map->grid[i];
		}
		symbol = ft_strchr(map->grid[i], EXIT);
		if (symbol)
		{
			end.x = i;
			end.y = symbol - map->grid[i];
		}
		i++;
	}
	return (is_path(map, start, end, &coins));
}

// check all map errors
bool	check_map_errors(t_map *map)
{
	if (!check_line_len(map))
		return (false);
	if (!check_map_symbols(map))
		return (false);
	if (!check_repeat(map))
		return (false);
	if (!check_borders(map))
		return (false);
	if (!check_if_boxed(map))
		return (false);
	if (!find_path(map))
		return (false);
	return (true);
}
