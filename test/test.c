/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:55:17 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/06 20:03:01 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char *argv[])
{
    t_map   *map;
    
    if (argc == 2)
    {
        map = create_game_map(argv[1]);
        if (!map)
            return (1);
        ft_print_grid(map->grid);
    }
    return (0);
}
