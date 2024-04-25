/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:30:08 by alicifer          #+#    #+#             */
/*   Updated: 2024/04/18 13:32:35 by alicifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_count_items(t_complete *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < (game->map_width))
		{
			if (game->map[y][x] == COLLECT)
				game->collect_count++;
			if (game->map[y][x] == PLAYER)
				game->player_count++;
			if (game->map[y][x] == MAP_EXIT)
				game->exit_count++;
			if (game->map[y][x] != WALL && game->map[y][x] != FLOOR &&
					game->map[y][x] != COLLECT && game->map[y][x] != PLAYER &&
					game->map[y][x] != MAP_EXIT)
				print_error("Invalid chars in the map.", game);
			x++;
		}
		y++;
	}
}

int	check_square(t_complete *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x] != '\n' && game->map[y][x] != '\0')
			x++;
		if (x != game->map_width)
			print_error("The map isn't squared.", game);
		y++;
	}
	return (1);
}

void	floodfill(t_complete *map_dup, int x, int y)
{
	if (x < 0 || y < 0 || y >= map_dup->map_height || x >= map_dup->map_width)
		return ;
	if (map_dup->map[y][x] == WALL)
		return ;
	if (map_dup->map[y][x] == COLLECT)
		map_dup->collect_count++;
	if (map_dup->map[y][x] == MAP_EXIT)
		map_dup->exit_count++;
	map_dup->map[y][x] = WALL;
	floodfill(map_dup, x, y - 1);
	floodfill(map_dup, x, y + 1);
	floodfill(map_dup, x - 1, y);
	floodfill(map_dup, x + 1, y);
}

int	check_floodfill(t_complete *game, char **argv)
{
	t_complete	*map_du;

	map_du = init_game();
	map_read(map_du, argv);
	check_count_items(map_du);
	map_du->map_width = ft_map_width(map_du->map[0]);
	floodfill(map_du, game->x_player, game->y_player);
	if (map_du->collect_count == game->collect_count && map_du->exit_count == 1)
	{
		free_all(map_du);
		return (1);
	}
	free_all(map_du);
	return (0);
}

int	check_map(t_complete *game, char **argv)
{
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		print_error("The argument isnt .ber", game);
	game->map_width = ft_map_width(game->map[0]);
	if (!check_walls(game))
		print_error("The map isn't valid!walls", game);
	if (!check_square(game))
		print_error("The map isn't valid!square", game);
	check_count_items(game);
	find_position_player(game);
	if (game->player_count != 1)
		print_error("The map isn't valid! Player", game);
	if (game->collect_count < 1)
		print_error("The map isn't valid! No collectibles.", game);
	if (game->exit_count != 1)
		print_error("The map isn't valid! invalid exit", game);
	if (!check_floodfill(game, argv))
		print_error("Collectibles or exit are not reachable", game);
	return (0);
}
