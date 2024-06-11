/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:04:04 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/11 23:23:59 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check that map is rectangular
bool	check_line_len(char **grid, int line_count)
{
	int	i;
	int	line_len;
	int	next_line_len;

	if (grid == NULL)
		return (false);
	i = 0;
	while (i < line_count)
	{
		line_len = ft_strlen(grid[i]);
		next_line_len = ft_strlen(grid[i + 1]);
		if (!(line_len == next_line_len))
		{
			if (i + 2 <= line_count)
				break ;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

// check for invalid map symbols
bool	check_map_symbols(char **grid, int line_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < line_count)
	{
		j = 0;
		while (grid[i][j] != '\n' && grid[i][j] != '\0')
		{
			if (grid[i][j] != SPACE && grid[i][j] != WALL && grid[i][j] != COIN
				&& grid[i][j] != EXIT && grid[i][j] != START)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

// check that there's one START, one EXIT and at least one COIN
bool	check_repeat(char **grid, int line_count)
{
	int	i;
	int	j;
	int	exit;
	int	start;
	int	coin;

	i = 0;
	exit = 0;
	start = 0;
	coin = 0;
	while (i < line_count)
	{
		j = 0;
		while (grid[i][j] != '\n' && grid[i][j] != '\0')
		{
			exit += grid[i][j] == EXIT;
			start += grid[i][j] == START;
			coin += grid[i][j] == COIN;
			j++;
		}
		i++;
	}
	return (exit == 1 && start == 1 && coin >= 1);
}

// check that map edges are WALL
bool	check_borders(char **grid, int line_count)
{
	int	i;
	int	j;

	i = 0;
	while (grid[0][i] != '\0' && grid[0][i] != '\n')
	{
		if (grid[0][i] != WALL)
			return (false);
		i++;
	}
	i = 1;
	while (i < line_count)
	{
		if (grid[i][0] != WALL && grid[i][ft_strlen(grid[i]) - 1] != WALL)
			return (false);
		i++;
	}
	j = 0;
	while (grid[i - 1][j] != '\0' && grid[i - 1][j] != '\n')
	{
		if (grid[i - 1][j] != WALL)
			return (false);
		j++;
	}
	return (true);
}

// check if symbols surrounded by WALL
bool	check_if_boxed(char **grid, int line_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < line_count)
	{
		j = 0;
		while (grid[i][j] != '\0' && grid[i][j] != '\n')
		{
			if (grid[i][j] == START || grid[i][j] == EXIT || grid[i][j] == COIN)
			{
				if ((j - 1 >= 0 && grid[i][j - 1] == WALL) && (j
						+ 1 < ft_strlen(grid[i]) && grid[i][j + 1] == WALL)
					&& (i - 1 >= 0 && grid[i - 1][j] == WALL) && (grid[i
						+ 1] != NULL && grid[i + 1][j] == WALL))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
