/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:27:15 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/04 18:16:25 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*create_game_map(char *file_path)
{
	int		fd;
	t_map	*map;

	fd = open_file(file_path);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map = read_file(fd, map);
	if (!map)
		return (NULL);
	close_file(fd);
	return (map);
}

// generates a texture
t_img	*create_texture(t_game *game, char *asset_path)
{
	t_img	*texture;

	texture = malloc(sizeof(t_img));
	if (!texture)
		return (NULL);
	texture->xpm = mlx_xpm_file_to_image(game->mlx, asset_path, &texture->w,
			&texture->h);
	texture->mlx = game->mlx;
	if (!texture->xpm)
		return (free(texture), handle_error(game), NULL);
	return (texture);
}

// load all textures
void	initialise_textures(t_game *game)
{
	game->map->coin = create_texture(game, COLLECTIBLE);
	game->map->wall = create_texture(game, PLATFORM);
	game->map->exit = create_texture(game, FINISH);
}
void	initialize_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (game->map->grid[i][j] != '\0' && game->map->grid[i][j] != '\n')
		{
			if (get_char(game->map->grid, game->map->rows, j, i) == START)
			{
				game->player = create_sprite(game, MARIO, j * TILE_SIZE, i
						* TILE_SIZE);
				return ;
			}
			j++;
		}
		i++;
	}
}

// check all map errors
bool	check_map_errors(t_map *map)
{
	if (!check_line_len(map))
		return (false);
	if (!check_map_symbols(map))
		return (false);
	if (!check_repeat(map))
		return (false);
	if (!check_borders(map))
		return (false);
	if (!check_if_boxed(map))
		return (false);
	if (!find_path(map))
		return (false);
	return (true);
}
