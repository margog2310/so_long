/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:18:32 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:23:46 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// draws pixel at a specific position
void	put_pixel_img(t_game *game_img, int x, int y, int colour)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < game_img->w && y < game_img->h)
	{
		dst = game_img->addr + (y * game_img->line_len + x * (game_img->bpp
					/ 8));
		*(unsigned int *)dst = colour;
	}
}

// draws a sprite on game screen
void	draw_sprite(t_game *game, t_sprite *sprite)
{
	mlx_put_image_to_window(game->mlx, game->win, sprite->texture->xpm,
		sprite->position.x, sprite->position.y);
}

// realloc modified for so_long
void	*ft_realloc_sl(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
			return (NULL);
		return (new_ptr);
	}
	if (!new_size)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

// prints error message and closes game
void	handle_error(t_game *game)
{
	ft_printf("Error\n");
	if (game)
		close_window(game);
}
