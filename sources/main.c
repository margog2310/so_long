/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:05:05 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/08 18:19:53 by margo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc == 2)
	{
		// read the map before you create the window so you can use the dimensions to draw the window
		game = new_window(1280, 900, "Game", argv[1]);
		if (!game || !game->mlx || !game->win)
			return (close_window(game), 1);
		draw_bgn((t_bgn){1280, 900, 1152000, 0x000000}, game);
		load_sprites(game);
		load_textures(game);
		mlx_mouse_hook(game->win, &mouse_event, 0);
		mlx_hook(game->win, KeyRelease, KeyReleaseMask, &on_keypress, game);
		mlx_hook(game->win, DestroyNotify, NoEventMask, close_window, game);
		mlx_loop(game->mlx);
		close_window(game);
	}
	else
		ft_printf("%s", "Error\n");
	return (0);
}
/* order of operations:
	1. open map.ber, read it and create the game map based on it
	2. use the dimensions of the game map to create the game struct and a the window
	3. draw the background and then load all textures based on the map
	4. load the sprites, begin animations and start the coin counter
	5. initialise the game loop and hooks
	6. load exit if game is won or reload game if game over
	7. display game over/victory message
	8. close window, destroy all images and free everything
	 */