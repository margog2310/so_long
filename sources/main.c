/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:05:05 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/15 16:41:54 by margo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	*create_game(char *file_path)
{
	t_game	*game;
	t_map	*map;

	map = create_game_map(file_path);
	if (!map)
		return (destroy_map(map), NULL);
	game = new_window(map->cols * TILE_SIZE, map->rows * TILE_SIZE, "Game");
	if (!game || !game->mlx || !game->win)
		return (destroy_map(map), close_window(game), NULL);
	game->map = map;
	draw_bgn((t_bgn){map->cols * TILE_SIZE, map->rows * TILE_SIZE, (map->cols
			* TILE_SIZE) * (map->rows * TILE_SIZE), 0x000000}, game);
	load_textures(game);
	return (game);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc == 2)
	{
		game = create_game(argv[1]);
		if (game)
		{
			mlx_mouse_hook(game->win, &mouse_event, 0);
			mlx_key_hook(game->win, &move_left, game);
			mlx_hook(game->win, KeyPress, KeyReleaseMask, &move_left, game);
			mlx_hook(game->win, DestroyNotify, NoEventMask, &close_window, game);
			//mlx_loop_hook(game->mlx, &render_all, game);
			mlx_loop(game->mlx);
			destroy_map(game->map);
			close_window(game);
		}
	}
	else
		ft_printf("%s", "Error\n");
	return (0);
}
/* order of operations:
	+ 1. open map.ber, read it and create the game map based on it
	+ 2. use the dimensions of the game map to create the game struct
			and a the window
	3. draw the background and then load all textures based on the map
	4. load the sprites, begin animations and start the coin counter
	5. initialise the game loop and hooks
	6. load exit if game is won or reload game if game over
	7. display game over/victory message
	8. close window, destroy all images and free everything
		*/