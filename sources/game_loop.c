/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:18:10 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/04 17:59:39 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	game_is_running(t_game *game)
{
	return (game->state.is_running);
}

int	handle_input(int keysym, t_game *game)
{
	if (keysym == D)
		move_right(game);
	if (keysym == A)
		move_left(game);
	if (keysym == W)
		move_up(game);
	if (keysym == S)
		move_down(game);
	if (keysym == ESC)
		close_window(game);
	return (0);
}

bool	check_collision(t_game *game, t_point next)
{
	t_bounds	player;

	player = player_bounds(game->player, next);
	if (check_wall_collision(game, player))
		return (true);
	collect_coins(game, player);
	if (has_won(game, player))
	{
		game->state.has_won = true;
		return (true);
	}		
	return (false);
}
