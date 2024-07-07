/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:32:45 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/07 21:29:51 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_right(t_game *game)
{
	if (!check_collision(game, (t_point){SPEED, 0}))
	{
		game->player->position.x += SPEED;
		game->player->direction = RIGHT;
		game->state.has_changed = true;
		print_moves(game);
	}
	return (0);
}

int	move_left(t_game *game)
{
	if (!check_collision(game, (t_point){-SPEED, 0}))
	{
		game->player->position.x -= SPEED;
		game->player->direction = LEFT;
		game->state.has_changed = true;
		print_moves(game);
	}
	return (0);
}

int	move_up(t_game *game)
{
	if (!check_collision(game, (t_point){0, -SPEED}))
	{
		game->player->position.y -= SPEED;
		//game->player->direction = UP;
		game->state.has_changed = true;
		print_moves(game);
	}
	return (0);
}

int	move_down(t_game *game)
{
	if (!check_collision(game, (t_point){0, SPEED}))
	{
		game->player->position.y += SPEED;
		//game->player->direction = DOWN;
		game->state.has_changed = true;
		print_moves(game);
	}
	return (0);
}

void	print_moves(t_game *game)
{
	game->move_counter++;
	ft_printf("Moves: %d\n", game->move_counter);
}
