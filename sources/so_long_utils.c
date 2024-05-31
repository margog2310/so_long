/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:18:32 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/31 01:55:39 by margo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
