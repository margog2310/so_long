/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:18:10 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/26 22:14:24 by mganchev         ###   ########.fr       */
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
	return (0);
}
