/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:27:15 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/11 22:53:53 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*create_game_map(char *file_path)
{
	int		fd;
	t_map	*map;

	fd = open_file(file_path);
	if (fd < 0)
		return (ft_printf("Error\n"), NULL);
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
		return (free(texture), close_window(game), NULL);
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
			if (get_char(game->map->grid, game->map->rows, j, i) == COIN)
				create_texture(game, COLLECTIBLE, j * TILE_SIZE, i * TILE_SIZE);
			if (get_char(game->map->grid, game->map->rows, j, i) == WALL)
				create_texture(game, PLATFORM, j * TILE_SIZE, i * TILE_SIZE);
			if (get_char(game->map->grid, game->map->rows, j, i) == START)
				create_sprite(game, MARIO, j * TILE_SIZE, i * TILE_SIZE);
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
			free_grid(map->grid, map->rows);
		if (map->textures)
			ft_lstclear(&map->textures, (void *)destroy_texture);
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