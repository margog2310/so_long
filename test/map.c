/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:27:15 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/07 01:45:44 by margo            ###   ########.fr       */
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
	if (!map)
		return (free(map), NULL);
	close_file(fd);
	return (map);
}

//  checks all possible map errors
bool	check_map_errors(char **grid, int line_count)
{
	if (!check_line_len(grid, line_count))
		return (false);
	if (!check_map_symbols(grid, line_count))
		return (false);
	if (!check_repeat(grid, line_count))
		return (false);
	if (!check_borders(grid, line_count))
		return (false);
	if (!check_if_boxed(grid, line_count))
		return (false);
	if (!find_path(grid, line_count))
		return (false);
	return (true);
}
