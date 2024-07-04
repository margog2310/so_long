/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:01 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/04 18:11:14 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

t_map	*read_file(int fd, t_map *map)
{
	int		line_count;
	char	*line;

	map->grid = NULL;
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->grid = ft_realloc_sl((void *)map->grid, sizeof(char *)
				* line_count, sizeof(char *) * (line_count + 1));
		if (!map->grid)
			return (NULL);
		map->grid[line_count] = line;
		line_count++;
		line = get_next_line(fd);
	}
	map->cols = ft_strlen(map->grid[0]) - 1;
	map->rows = line_count;
	if (check_map_errors(map) != true)
		return (NULL);
	return (map);
}

void	free_grid(char **grid, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int	close_file(int fd)
{
	if (close(fd) < 0)
		return (0);
	return (1);
}
