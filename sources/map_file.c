/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:01 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/28 22:04:38 by mganchev         ###   ########.fr       */
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

	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		grid[line_count] = line;
		line_count++;
	}
	if (check_line_len(grid) != 1)
		return (free_grid(grid), NULL);
	map->grid = grid;
	map->x = ft_strlen(line);
	map->y = line_count;
	return (map);
}
void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
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