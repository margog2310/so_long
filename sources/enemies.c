/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:47:48 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/07 22:51:42 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialise_enemy_textures(t_game *game, t_sprite *goomba)
{
	goomba->animations = malloc(sizeof(t_animation));
	goomba->animations->frame_count = 2;
	goomba->animations->frames = malloc(2 * sizeof(t_img));
	goomba->animations->frames[0] = create_texture(game, ENEMY_ANIM1);
	goomba->animations->frames[1] = create_texture(game, ENEMY_ANIM2);
	goomba->dead = create_texture(game, ENEMY_DEAD);
	goomba->animations->current_frame = 0;
	goomba->is_moving = false;
}

void	initialize_enemies(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->enemy_index = 0;
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->grid[i][j])
		{
			if (game->map->grid[i][j] == MONSTER)
			{
				game->goombas = ft_realloc_sl(game->goombas, game->enemy_index
						* sizeof(t_sprite), (game->enemy_index + 1)
						* sizeof(t_sprite));
				game->goombas[game->enemy_index] = create_sprite(game,
						ENEMY_ANIM1, j * TILE_SIZE, i * TILE_SIZE);
				initialise_enemy_textures(game,
					game->goombas[game->enemy_index]);
				game->enemy_index++;
			}
			j++;
		}
		i++;
	}
}

void	destroy_enemies(t_game *game)
{
	if (game->goombas)
	{
		while (--game->enemy_index >= 0)
			destroy_sprite(game->goombas[game->enemy_index]);
		free(game->goombas);
	}
}
