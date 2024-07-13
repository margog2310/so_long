/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:18:10 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/13 02:16:57 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	game_is_running(t_game *game)
{
	return (game->state.is_running);
}

bool	player_is_moving(t_game *game)
{
	return (game->player->is_moving);
}

int	handle_input(int keysym, t_game *game)
{
	if (keysym == W || keysym == A || keysym == S || keysym == D)
	{
		game->player->is_moving = true;
		if (keysym == D)
			move_right(game);
		if (keysym == A)
			move_left(game);
		if (keysym == W)
			move_up(game);
		if (keysym == S)
			move_down(game);
	}
	else if (keysym == ESC)
		close_window(game);
	return (0);
}

void	update_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_index)
	{
		enemy_patrol(game, game->goombas[i]);
		i++;
	}
}

bool	check_collision(t_game *game, t_point next)
{
	t_bounds	player;

	player = sprite_bounds(game->player, next);
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
