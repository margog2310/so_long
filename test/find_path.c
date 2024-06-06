/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:19:30 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/06 19:40:41 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// checks that a cell is valid
bool	is_valid(char **grid, bool **visited, int row, int col)
{
	int	rows;
	int	cols;

	ft_grid_size(grid, &rows, &cols);
	return ((row >= 0) && (row < rows) && (col >= 0) && (col < cols)
		&& (grid[row][col] != WALL) && (!visited[row][col]));
}
// implements DFS algorithm + coin count
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
				+ row_vector[i], current.y + col_vector[i]}, coins);
		i++;
	}
}
// initialises DFS algorithm
bool	is_path(char **grid, t_point start, t_point end, int *coins)
{
	int		i;
	int		rows;
	int		cols;
	bool	**visited;

	i = 0;
	ft_grid_size(grid, &rows, &cols);
	visited = (bool **)ft_allocate_grid(rows, cols, sizeof(bool));
	depth_first_search(grid, visited, start, coins);
	if (visited[end.x][end.y])
		return (free_grid((char **)visited), true);
	return (free_grid((char **)visited), false);
}
// locates START and EXIT and finds a path
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
		symbol = ft_strchr(grid[i], START);
		if (symbol)
		{
			start.x = i;
			start.y = symbol - grid[i];
		}
		symbol = ft_strchr(grid[i], EXIT);
		if (symbol)
		{
			end.x = i;
			end.y = symbol - grid[i];
		}
		i++;
	}
	return (is_path(grid, start, end, &coins));
}
