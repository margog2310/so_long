/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:19:30 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/30 23:12:15 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid(char **grid, bool **visited, int row, int col)
{
	int	rows;
	int	cols;

	rows = sizeof(grid) / sizeof(grid[0]);
	cols = sizeof(grid[0]) / sizeof(grid[0][0]);
	return ((row >= 0) && (row < rows) && (col >= 0) && (col < cols)
		&& (grid[row][col] != WALL) && (!visited[row][col]));
}

void	depth_first_search(char **grid, bool **visited, t_point current,
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
	if (grid[current.x][current.y] == COIN)
		(*coins)++;
	i = 0;
	while (i < 4)
	{
		if (is_valid(grid, visited, current.x + row_vector[i], current.y
				+ col_vector[i]))
			depth_first_search(grid, visited, (t_point){current.x
				+ row_vector[i], current.y + col_vector[i]}, &coins);
		i++;
	}
}

bool	is_path(char **grid, t_point start, t_point end, int *coins)
{
	int		i;
	int		rows;
	int		cols;
	bool	**visited;

	i = 0;
	rows = sizeof(grid) / sizeof(grid[0]);
	cols = sizeof(grid[0]) / sizeof(grid[0][0]);
	visited = malloc(rows * sizeof(bool *));
	while (i < rows)
	{
		visited[i] = malloc(cols * sizeof(bool));
		i++;
	}
	depth_first_search(grid, visited, start, coins);
	if (visited[end.x][end.y])
	{
		free_grid(visited);
		return (true);
	}
	return (false);
}
bool	find_path(char **grid)
{
	int		i;
	int		coins;
	char	*symbol;
	t_point	start;
	t_point	end;

	i = 0;
	coins = 0;
	while (grid[i] != NULL)
	{
		if ((symbol = ft_strchr(grid[i], START)))
		{
			start.x = i;
			start.y = symbol - grid[i];
		}
		if ((symbol = ft_strchr(grid[i], EXIT)))
		{
			end.x = i;
			end.y = symbol - grid[i];
		}
		i++;
	}
	return (is_path(grid, start, end, &coins));
}
