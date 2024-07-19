/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:18:10 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:12:37 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// checks game state
bool	game_is_running(t_game *game)
{
	return (game->state.is_running);
}

// checks player state
bool	player_is_moving(t_game *game)
{
	return (game->player->is_moving);
}

// manages key input from player
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

// manages collisions between player and enemies
bool	player_enemy_collision(t_bounds player, t_sprite *goomba)
{
	t_bounds	goomba_bounds;

	goomba_bounds = sprite_bounds(goomba, goomba->position);
	if (check_bounds(player, goomba_bounds))
		return (true);
	return (false);
}

// manages player collisions
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
