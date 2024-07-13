/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:47:48 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/13 02:43:44 by mganchev         ###   ########.fr       */
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

t_sprite	*create_goomba(t_game *game, t_sprite *goomba, int x, int y)
{
	goomba = create_sprite(game, ENEMY_ANIM1, x, y);
	initialise_enemy_textures(game, goomba);
	mlx_put_image_to_window(game->mlx, game->win, goomba->texture->xpm, x, y);
	return (goomba);
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
				game->goombas[game->enemy_index] = create_goomba(game,
						game->goombas[game->enemy_index], j * TILE_SIZE, i
						* TILE_SIZE);
				game->enemy_index++;
			}
			j++;
		}
		i++;
	}
}

int	enemy_patrol(t_game *game, t_sprite *goomba)
{
	static clock_t	last_move = 0;
	clock_t			current_time;
	double			time_since_last_move;

	current_time = clock();
	time_since_last_move = (double)(current_time - last_move) / CLOCKS_PER_SEC;
	if (time_since_last_move >= PATROL_DELAY)
	{
		if (goomba->direction == LEFT)
		{
			if (!check_enemy_collision(game, goomba, (t_point){-SPEED, 0}))
				goomba->position.x -= SPEED;
			else
				goomba->direction = RIGHT;
		}
		else if (goomba->direction == RIGHT)
		{
			if (!check_enemy_collision(game, goomba, (t_point){SPEED, 0}))
				goomba->position.x += SPEED;
			else
				goomba->direction = LEFT;
		}
		last_move = current_time;
	}
	return (0);
}

bool	check_enemy_collision(t_game *game, t_sprite *goomba, t_point next)
{
	t_bounds	goomba_bounds;

	goomba_bounds = sprite_bounds(goomba, next);
	if (check_wall_collision(game, goomba_bounds))
		return (true);
	return (false);
}
