/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:01 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/06 23:25:26 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	return (fd);
}

t_map	*read_file(int fd, t_map *map)
{
	int		line_count;
	char	*line;
	char	**grid;

	grid = NULL;
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		grid = ft_realloc((void *)grid, sizeof(char*) * (line_count + 1));
		if (!grid)
			return (NULL);
		grid[line_count] = line;
		line_count++;
		line = get_next_line(fd);
	}
	if (check_map_errors(grid, line_count) != true)
		return (free_grid(grid, line_count), NULL);
	map->grid = grid;
	map->x = ft_strlen(grid[0]);
	map->y = line_count;
	ft_grid_size(map->grid, &map->rows, &map->cols);
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

int	free_file(char *buffer)
{
	if (buffer)
		free(buffer);
	else
		return (0);
	return (1);
}

int	close_file(int fd)
{
	if (close(fd) < 0)
		return (0);
	return (1);
}
