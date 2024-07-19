/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:38:31 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:25:34 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// animating player if moving right
void	move_right_animation(t_game *game, t_sprite *player)
{
	mlx_put_image_to_window(game->mlx, game->win,
		player->animations->frames[player->animations->current_frame]->xpm,
		player->position.x, player->position.y);
	player->animations->current_frame++;
	if (player->animations->current_frame > 2)
		player->animations->current_frame = 0;
}

// animating player if moving left
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

// animate player
void	update_player_animation(t_game *game, t_sprite *player)
{
	if (player->is_moving)
	{
		if (player->direction == RIGHT)
			move_right_animation(game, player);
		if (player->direction == LEFT)
			move_left_animation(game, player);
	}
	else if (!player->is_moving && !player->is_dead)
		draw_sprite(game, player);
	else if (player->is_dead)
		mlx_put_image_to_window(game->mlx, game->win, player->dead->xpm,
			player->position.x, player->position.y);
}

// animate enemies
void	update_goomba_animation(t_game *game, t_sprite *goomba)
{
	void	*blank;

	if (goomba)
	{
		if (goomba->previous.x == 0 && goomba->previous.y == 0)
			goomba->previous = goomba->position;
		if (goomba->position.x != goomba->previous.x
			|| goomba->position.y != goomba->previous.y)
		{
			blank = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
			mlx_put_image_to_window(game->mlx, game->win, blank,
				goomba->previous.x, goomba->previous.y);
			mlx_destroy_image(game->mlx, blank);
		}
		mlx_put_image_to_window(game->mlx, game->win,
			goomba->animations->frames[goomba->animations->current_frame]->xpm,
			goomba->position.x, goomba->position.y);
		goomba->animations->current_frame++;
		if (goomba->animations->current_frame
			>= goomba->animations->frame_count)
			goomba->animations->current_frame = 0;
		goomba->previous = goomba->position;
	}
}

// animate coins
void	update_coin_animation(t_game *game, t_coin *coin)
{
	clock_t	current_time;
	double	time_since_last_frame;

	if (coin)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			coin->animations->frames[coin->animations->current_frame]->xpm,
			coin->position.x, coin->position.y);
		current_time = clock();
		time_since_last_frame = (double)(current_time - coin->last_frame_time)
			/ CLOCKS_PER_SEC;
		if (time_since_last_frame >= coin->delay)
		{
			coin->animations->current_frame++;
			if (coin->animations->current_frame
				>= coin->animations->frame_count)
				coin->animations->current_frame = 0;
			coin->last_frame_time = current_time;
		}
	}
}
