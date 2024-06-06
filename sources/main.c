/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:05:05 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/06 19:48:11 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	(void)argc;
	game = new_window(1280, 900, "Game");
	if (!game || !game->mlx || !game->win)
		return (close_window(game), 1);
	if (!create_game_map(argv[1]))
		return (close_window(game), 1);
	if (!load_sprites(game))
		return (close_window(game), 1);
	draw_bgn((t_bgn){1280, 900, 1152000, 0x000000}, game);
	mlx_mouse_hook(game->win, &mouse_event, 0);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &on_keypress, &game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
	close_window(game);
	return (0);
}
