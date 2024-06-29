/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:04:04 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/29 19:45:28 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check that map is rectangular
bool	check_line_len(t_map *map)
{
	int	i;
	int	line_len;
	int	next_line_len;

	if (map->grid == NULL)
		return (false);
	i = 0;
	while (i < map->rows)
	{
		line_len = ft_strlen(map->grid[i]);
		next_line_len = ft_strlen(map->grid[i + 1]);
		if (!(line_len == next_line_len))
		{
			if (i + 2 <= map->rows)
				break ;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

// check for invalid map symbols
bool	check_map_symbols(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j] != '\n' && map->grid[i][j] != '\0')
		{
			if (map->grid[i][j] != SPACE && map->grid[i][j] != WALL
				&& map->grid[i][j] != COIN && map->grid[i][j] != EXIT
				&& map->grid[i][j] != START)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

// check that there's one START, one EXIT and at least one COIN
bool	check_repeat(t_map *map)
{
	int	i;
	int	j;
	int	exit;
	int	start;

	i = 0;
	exit = 0;
	start = 0;
	map->coins = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j] != '\n' && map->grid[i][j] != '\0')
		{
			exit += map->grid[i][j] == EXIT;
			start += map->grid[i][j] == START;
			map->coins += map->grid[i][j] == COIN;
			j++;
		}
		i++;
	}
	return (exit == 1 && start == 1 && map->coins >= 1);
}

// check that map edges are WALL
bool	check_borders(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[0][i] != '\0' && map->grid[0][i] != '\n')
	{
		if (map->grid[0][i] != WALL)
			return (false);
		i++;
	}
	i = 1;
	while (i < map->rows)
	{
		if (map->grid[i][0] != WALL && map->grid[i][map->cols - 1] != WALL)
			return (false);
		i++;
	}
	j = 0;
	while (map->grid[i - 1][j] != '\0' && map->grid[i - 1][j] != '\n')
	{
		if (map->grid[i - 1][j] != WALL)
			return (false);
		j++;
	}
	return (true);
}

// check if symbols surrounded by WALL
bool	check_if_boxed(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid[i][j] != '\0' && map->grid[i][j] != '\n')
		{
			if (map->grid[i][j] == START || map->grid[i][j] == EXIT
				|| map->grid[i][j] == COIN)
			{
				if ((j - 1 >= 0 && map->grid[i][j - 1] == WALL) && (j
						+ 1 < ft_strlen(map->grid[i]) && map->grid[i][j
						+ 1] == WALL) && (i - 1 >= 0 && map->grid[i
						- 1][j] == WALL) && (map->grid[i + 1] != NULL
						&& map->grid[i + 1][j] == WALL))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
