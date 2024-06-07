/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:05:05 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/07 22:29:26 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc == 2)
	{
		game = new_window(1280, 900, "Game");
		if (!game || !game->mlx || !game->win)
			return (close_window(game), 1);
		game->map = create_game_map(argv[1]);
		if (!game->map)
			return (close_window(game), 1);
		if (!load_sprites(game))
			return (close_window(game), 1);
		draw_bgn((t_bgn){1280, 900, 1152000, 0x000000}, game);
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
