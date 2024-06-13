/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:08:21 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/13 18:23:09 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int  render_all(t_game *game)
{
    if ((t_sprite *)(game->sprites->content)->has_moved == true)
    {
        mlx_clear_window(game->mlx, game->win);
        draw_bgn((t_bgn){game->map->cols * TILE_SIZE, game->map->rows * TILE_SIZE, (game->map->cols
                * TILE_SIZE) * (game->map->rows * TILE_SIZE), 0x000000}, game);
        load_textures(game);
        mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    }
    return (0);
}
