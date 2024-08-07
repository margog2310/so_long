/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:05:05 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/19 15:14:40 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// starts up game
t_game	*create_game(char *file_path)
{
	t_game	*game;
	t_map	*map;

	map = create_game_map(file_path);
	if (!map)
		return (destroy_map(map), ft_printf("Error: Invalid map\n"), NULL);
	game = new_window(map->cols * TILE_SIZE, (map->rows * TILE_SIZE) + 16,
			"Super Mario");
	if (!game || !game->mlx || !game->win)
		return (handle_error(game), NULL);
	game->map = map;
	game->file_path = file_path;
	initialise_game_state(game);
	return (game);
}

// starts up game state
void	initialise_game_state(t_game *game)
{
	game->state.is_running = true;
	game->state.has_changed = true;
	game->state.has_won = false;
	game->state.has_lost = false;
	initialise_textures(game);
	initialize_player(game);
	initialise_coins(game);
	initialize_enemies(game);
	load_textures(game);
}

// manages game loop
int	game_loop(t_game *game)
{
	if (game->state.is_running)
	{
		update_game_state(game);
		render_all(game);
	}
	if (game->state.has_won)
		close_window(game);
	if (game->state.has_lost)
	{
		update_player_animation(game, game->player);
		usleep(1000000);
		close_window(game);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*extension;
	t_game	*game;

	if (argc == 2)
	{
		extension = ft_strrchr(argv[1], '.');
		if (!extension || ft_strncmp(extension, ".ber",
				(size_t)ft_strlen(extension)) != 0)
		{
			ft_printf("Error: Invalid file extension.\n");
			return (1);
		}
		game = create_game(argv[1]);
		if (game)
		{
			mlx_hook(game->win, KeyPress, KeyPressMask, handle_input, game);
			mlx_hook(game->win, DestroyNotify, NoEventMask, close_window, game);
			mlx_loop_hook(game->mlx, &game_loop, game);
			mlx_loop(game->mlx);
			close_window(game);
		}
	}
	else
		ft_printf("Error: Invalid file/arguments\n");
	return (0);
}

/*
BONUS:
		2. clean up code + test
		3. create default map + example maps
*/