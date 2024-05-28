/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:04:04 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/28 23:13:43 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_line_len(char **grid)
{
	int	i;
	int	line_len;
	int	next_line_len;

	i = 0;
	while (grid != NULL)
	{
		line_len = ft_strlen(grid[i]);
		next_line_len = ft_strlen(grid[i + 1]);
		if (!(line_len == next_line_len))
			return (0);
		i++;
	}
	return (1);
}
int	check_map_symbols(char **grid)
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
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
// 1. check if exit/start repeats
// 2. check borders
// 3. check that start/exit/coins are not blocked for the player
// 5. check that there's (only) 1 start, (only) 1 exit and (at least) 1 coin
// 6. check that there's a valid path (whatever tf that means)