/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:05:05 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/31 02:05:37 by margo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_game	*game;

	game = new_window(1280, 900, "Game");
	if (!game || !game->mlx || !game->win)
		return (close_window(game), 1);
	draw_bgn((t_bgn){1280, 900, 1152000, 0x000000}, game);
	mlx_mouse_hook(game->win, &mouse_event, 0);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &on_keypress, &game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
	close_window(game);
	return (0);
}
