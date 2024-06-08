/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:27:15 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/08 18:10:29 by margo            ###   ########.fr       */
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
// generates a texture
t_img	*create_texture(t_game *game, char *asset_path, int x, int y)
{
	t_img		*texture;

	texture = malloc(sizeof(t_img));
	if (!texture)
		return (NULL);
	texture->xpm = mlx_xpm_file_to_image(game->mlx, asset_path, &texture->w,
			&texture->h);
	texture->mlx = game->mlx;
	if (!texture->xpm)
		return (close_window(game), NULL);
	ft_lstadd_back(&game->map->textures, ft_lstnew(texture));
	mlx_put_image_to_window(game->mlx, game->win, texture->xpm, x, y);
	return (texture);
}
// load all textures
void	load_textures(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (game->map->grid[i][j] != '\0' && game->map->grid[i][j] != '\n')
		{
			if (get_char(game->map->grid, game->map->rows, i * 32, j * 32) == COIN)
				create_texture(game, COLLECTIBLE, i, j);
			j++;
		}
		i++;
	}
}
//  checks all possible map errors
void	destroy_map(t_map *map)
{
	if (map)
	{
		if (map->grid)
			free_grid(map->grid, map->y);
		free(map);
	}
}
// destroy a texture
void	*destroy_texture(t_img *texture)
{
	if (texture->xpm)
		mlx_destroy_image(texture->mlx, texture->xpm);
	free(texture);
	texture = NULL;
	return (NULL);
}