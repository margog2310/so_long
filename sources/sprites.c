/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:35:26 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/04 16:56:37 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprite	*create_sprite(t_game *game, char *asset_path, int x, int y)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->texture = create_texture(game, asset_path);
	sprite->position.x = x;
	sprite->position.y = y;
	sprite->velocity.x = 0;
	sprite->velocity.y = 0;
	return (sprite);
}

/*int	player_jump(int	keysym, t_game *game)
{
	// do movement up (jump) + 3 more for other directions
}*/
void	draw_sprite(t_game *game, t_sprite *sprite)
{
	mlx_put_image_to_window(game->mlx, game->win, sprite->texture->xpm,
		sprite->position.x, sprite->position.y);
}
