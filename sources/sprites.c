/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:35:26 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/13 18:24:14 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprite	*create_sprite(t_game *game, char *asset_path, int x, int y)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->texture = create_texture(game, asset_path, x, y);
	sprite->position.x = x;
	sprite->position.y = y;
	ft_lstadd_back(&game->sprites, ft_lstnew(sprite));
	return (sprite);
}

/*int	player_jump(int	keysym, t_game *game)
{
	// do movement up (jump) + 3 more for other directions
}*/

int	move_left(int keysym, t_game *game)
{
	t_sprite	*player;

	if (keysym == D)
	{
		player = (t_sprite *)game->sprites;
		player->position.x += 16;
		player->direction = 2;
		game->has_changed = true;
	}
	return (0);
}