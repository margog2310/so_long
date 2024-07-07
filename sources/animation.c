/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:38:31 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/07 23:02:32 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_right_animation(t_game *game, t_sprite *player)
{
	mlx_put_image_to_window(game->mlx, game->win,
		player->animations->frames[player->animations->current_frame]->xpm,
		player->position.x, player->position.y);
	player->animations->current_frame++;
	if (player->animations->current_frame > 2)
		player->animations->current_frame = 0;
}

void	move_left_animation(t_game *game, t_sprite *player)
{
	mlx_put_image_to_window(game->mlx, game->win,
		player->animations->frames[player->animations->current_frame]->xpm,
		player->position.x, player->position.y);
	player->animations->current_frame++;
	if (player->animations->current_frame > 5
		|| player->animations->current_frame < 3)
		player->animations->current_frame = 3;
}

void	update_player_animation(t_game *game, t_sprite *player)
{
	if (player->is_moving)
	{
		if (player->direction == RIGHT)
			move_right_animation(game, player);
		if (player->direction == LEFT)
			move_left_animation(game, player);
	}
	if (!player->is_moving)
		draw_sprite(game, player);
	if (player->is_dead)
		mlx_put_image_to_window(game->mlx, game->win, player->dead->xpm,
			player->position.x, player->position.y);
}

void	update_goomba_animation(t_game *game, t_sprite *goomba)
{
	if (goomba->is_moving)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			goomba->animations->frames[goomba->animations->current_frame]->xpm,
			goomba->position.x, goomba->position.y);
		goomba->animations->current_frame++;
		if (goomba->animations->current_frame >= goomba->animations->frame_count)
			goomba->animations->current_frame = 0;
	}
	if (goomba->is_dead)
		mlx_put_image_to_window(game->mlx, game->win, goomba->dead->xpm,
			goomba->position.x, goomba->position.y);
}