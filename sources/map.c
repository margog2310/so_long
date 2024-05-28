/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:29:49 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/28 22:04:27 by mganchev         ###   ########.fr       */
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
    
}
