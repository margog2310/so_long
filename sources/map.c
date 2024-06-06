/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:27:15 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/06 19:59:28 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

t_map	*create_game_map(char *file_path)
{
	int		fd;
	t_map	*map;

	fd = open_file(file_path);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map = read_file(fd, map);
	if (!map || check_map_errors(map->grid) == false)
		return (free(map), NULL);
	close_file(fd);
	return (map);
}

//  checks all possible map errors
bool	check_map_errors(char **grid)
{
	if (!check_line_len(grid))
		return (false);
	if (!check_map_symbols(grid))
		return (false);
	if (!check_repeat(grid))
		return (false);
	if (!check_borders(grid))
		return (false);
	if (!check_if_boxed(grid))
		return (false);
	return (true);
}
