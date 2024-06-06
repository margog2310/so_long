/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:29:49 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/06 18:21:10 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*create_game_map(char *file_path, t_game *game)
{
	int		fd;
	t_map	*map;

	fd = open_file(file_path);
	map = malloc(sizeof(t_map));
	if (!map)
		return (close_window(game), NULL);
	map = read_file(fd, map);
	if (!map || check_map_errors(map->grid) == false)
		return(close_window(game), NULL);
}

//  checks all possible map errors
bool	check_map_errors(char **grid)
{
	if (!check_line_len(grid))
		return (false);
	if (!check_map_symbol(grid))
		return (false);
	if (!check_repeat(grid))
		return (false);
	if (!check_borders(grid))
		return (false);
	if (!check_if_boxed(grid))
		return (false);
	return (true);
}
