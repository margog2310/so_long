/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:38:31 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/13 03:15:55 by mganchev         ###   ########.fr       */
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
	else if (!player->is_moving)
		draw_sprite(game, player);
	else if (player->is_dead)
		mlx_put_image_to_window(game->mlx, game->win, player->dead->xpm,
			player->position.x, player->position.y);
}

void	update_goomba_animation(t_game *game, t_sprite *goomba)
{
	static t_point	previous = {0, 0};
	void			*blank;

	if (goomba)
	{
		if (previous.x == 0 && previous.y == 0)
			previous = goomba->position;
		if (goomba->position.x != previous.x
			|| goomba->position.y != previous.y)
		{
			blank = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
			mlx_put_image_to_window(game->mlx, game->win, blank, previous.x,
				previous.y);
			mlx_destroy_image(game->mlx, blank);
		}
		mlx_put_image_to_window(game->mlx, game->win,
			goomba->animations->frames[goomba->animations->current_frame]->xpm,
			goomba->position.x, goomba->position.y);
		goomba->animations->current_frame++;
		if (goomba->animations->current_frame >= goomba->animations->frame_count)
			goomba->animations->current_frame = 0;
		previous = goomba->position;
	}
}

void	update_coin_animation(t_game *game, t_coin *coin)
{
	static clock_t	last_frame_time = 0;
	clock_t			current_time;
	double			time_since_last_frame;

	if (coin)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			coin->animations->frames[coin->animations->current_frame]->xpm,
			coin->position.x, coin->position.y);
		current_time = clock();
		time_since_last_frame = (double)(current_time - last_frame_time)
			/ CLOCKS_PER_SEC;
		if (time_since_last_frame >= DELAY)
		{
			coin->animations->current_frame++;
			if (coin->animations->current_frame >= coin->animations->frame_count)
				coin->animations->current_frame = 0;
			last_frame_time = current_time;
		}
	}
}
