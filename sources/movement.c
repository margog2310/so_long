/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:32:45 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:18:45 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// player movement for D key
int	move_right(t_game *game)
{
	if (!check_collision(game, (t_point){SPEED, 0}))
	{
		game->player->position.x += SPEED;
		game->player->direction = RIGHT;
		game->state.has_changed = true;
	}
	return (0);
}

// player movement for A key
int	move_left(t_game *game)
{
	if (!check_collision(game, (t_point){-SPEED, 0}))
	{
		game->player->position.x -= SPEED;
		game->player->direction = LEFT;
		game->state.has_changed = true;
	}
	return (0);
}

// player movement for W key
int	move_up(t_game *game)
{
	if (!check_collision(game, (t_point){0, -SPEED}))
	{
		game->player->position.y -= SPEED;
		game->state.has_changed = true;
	}
	return (0);
}

// player movement for S key
int	move_down(t_game *game)
{
	if (!check_collision(game, (t_point){0, SPEED}))
	{
		game->player->position.y += SPEED;
		game->state.has_changed = true;
	}
	return (0);
}

// prints number of moves on screen and in terminal
void	print_moves(t_game *game)
{
	char	*moves;

	game->move_counter++;
	moves = ft_itoa(game->move_counter);
	ft_printf("Moves: %d\n", game->move_counter);
	mlx_string_put(game->mlx, game->win, 0, (game->map->rows * TILE_SIZE) + 16,
		16777215, "Moves:");
	mlx_string_put(game->mlx, game->win, 60, (game->map->rows * TILE_SIZE) + 16,
		16777215, moves);
	free(moves);
}
