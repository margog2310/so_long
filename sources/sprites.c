/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:35:26 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/24 01:30:57 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	*create_sprite(t_game *game, char *asset_path)
{
	t_img	*sprite;

	sprite = malloc(sizeof(t_img));
	if (!sprite)
		close_window(game);
	sprite->xpm = mlx_xpm_file_to_image(game->mlx, asset_path, &sprite->w,
			&sprite->h);
	sprite->mlx = game->mlx;
	if (!sprite->xpm)
		close_window(game);
	ft_lstadd_back(&game->sprites, ft_lstnew(sprite));
	mlx_put_image_to_window(game->mlx, game->win, sprite->xpm, 150, 150);
	return (sprite);
}
t_img	*load_sprites(t_game *game)
{
	t_img	*mario_sprite;

	mario_sprite = create_sprite(game, MARIO);
	if (!mario_sprite)
		return (close_window(game), NULL);
	return (mario_sprite);
}
void	*destroy_sprite(t_img *sprite)
{
	if (sprite->xpm)
		mlx_destroy_image(sprite->mlx, sprite->xpm);
	free(sprite);
	sprite = NULL;
	return (NULL);
}
