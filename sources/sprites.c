/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:35:26 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:24:37 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// creates a new sprite
t_sprite	*create_sprite(t_game *game, char *asset_path, int x, int y)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->texture = create_texture(game, asset_path);
	sprite->position.x = x;
	sprite->position.y = y;
	sprite->is_dead = false;
	sprite->is_moving = false;
	sprite->direction = RIGHT;
	return (sprite);
}

// locates player position on game map and places sprite
void	initialize_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->cols)
		{
			if (game->map->grid[i][j] == START)
			{
				game->player = create_sprite(game, MARIO, j * TILE_SIZE, i
						* TILE_SIZE);
				initialise_player_textures(game);
				return ;
			}
			j++;
		}
		i++;
	}
}

// loads player textures
void	initialise_player_textures(t_game *game)
{
	game->player->animations = malloc(sizeof(t_animation));
	game->player->animations->frame_count = 6;
	game->player->animations->frames = malloc(6 * sizeof(t_img));
	game->player->animations->frames[0] = create_texture(game, ANIM1_RIGHT);
	game->player->animations->frames[1] = create_texture(game, ANIM2_RIGHT);
	game->player->animations->frames[2] = create_texture(game, ANIM3_RIGHT);
	game->player->animations->frames[3] = create_texture(game, ANIM1_LEFT);
	game->player->animations->frames[4] = create_texture(game, ANIM2_LEFT);
	game->player->animations->frames[5] = create_texture(game, ANIM3_LEFT);
	game->player->dead = create_texture(game, MARIO_DEAD);
	game->player->animations->current_frame = 0;
	game->player->is_moving = false;
}

// clears a sprite
void	destroy_sprite(t_sprite *sprite)
{
	if (sprite)
	{
		if (sprite->animations)
			destroy_animations(sprite->animations);
		if (sprite->texture)
			free_images(sprite->texture);
		if (sprite->dead)
			free_images(sprite->dead);
		free(sprite);
	}
}
