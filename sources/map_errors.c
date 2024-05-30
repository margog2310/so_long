/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:04:04 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/30 20:33:21 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_line_len(char **grid)
{
	int	i;
	int	line_len;
	int	next_line_len;

	if (grid == NULL)
		return (false);
	i = 0;
	while (grid != NULL)
	{
		line_len = ft_strlen(grid[i]);
		next_line_len = ft_strlen(grid[i + 1]);
		if (!(line_len == next_line_len))
			return (false);
		i++;
	}
	return (true);
}

bool	check_map_symbols(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
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

bool	check_repeat(char **grid)
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
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
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

bool	check_borders(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[0][i] != '\0')
	{
		if (grid[0][i] != WALL)
			return (false);
		i++;
	}
	i = 1;
	while (grid[i] != NULL)
	{
		if (grid[i][0] != WALL || grid[i][ft_strlen(grid[i]) - 1] != WALL)
			return (false);
		i++;
	}
	j = 0;
	while (grid[--i][j] != '\0')
	{
		if (grid[i][j] != WALL)
			return (false);
		j++;
	}
	return (true);
}

bool	check_path(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (grid[i][j] == START || grid[i][j] == EXIT || grid[i][j] == COIN)
			{
				if (j - 1 >= 0 && grid[i][j - 1] != WALL)
					return (false);
				if (j + 1 < ft_strlen(grid[i]) && grid[i][j + 1] != WALL)
					return (false);
				if (i - 1 >= 0 && grid[i - 1][j] != WALL)
					return (false);
				if (grid[i + 1] != NULL && grid[i + 1][j] != WALL)
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
