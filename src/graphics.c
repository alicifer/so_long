/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:55:26 by alicifer          #+#    #+#             */
/*   Updated: 2024/04/17 16:12:58 by alicifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	txt_to_game(t_complete *game)
{
	game->mlx = mlx_init(game->map_width * 64,
			game->map_height * 64, "so_long", false);
	game->floor_t = mlx_load_png("./sprites/floor.png");
	game->exit_t = mlx_load_png("./sprites/exit.png");
	game->player_t = mlx_load_png("./sprites/player.png");
	game->wall_t = mlx_load_png("./sprites/wall.png");
	game->collect_t = mlx_load_png("./sprites/collect.png");
	if (!game->floor_t || !game->exit_t || !game->player_t
		|| !game->wall_t || !game->collect_t)
		return ;
	game->floor_i = mlx_texture_to_image(game->mlx, game->floor_t);
	game->exit_i = mlx_texture_to_image(game->mlx, game->exit_t);
	game->player_i = mlx_texture_to_image(game->mlx, game->player_t);
	game->wall_i = mlx_texture_to_image(game->mlx, game->wall_t);
	game->collect_i = mlx_texture_to_image(game->mlx, game->collect_t);
	if (!game->floor_i || !game->exit_i
		|| !game->player_i || !game->wall_i || !game->collect_i)
		return ;
}

void	load_imgs(t_complete *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == FLOOR || game->map[y][x] == COLLECT
				|| game->map[y][x] == PLAYER)
				mlx_image_to_window(game->mlx, game->floor_i, x * IMG, y * IMG);
			if (game->map[y][x] == WALL)
				mlx_image_to_window(game->mlx, game->wall_i, x * IMG, y * IMG);
			if (game->map[y][x] == COLLECT)
				mlx_image_to_window(game->mlx, game->collect_i, x * IMG,
					y * IMG);
			if (game->map[y][x] == MAP_EXIT)
				mlx_image_to_window(game->mlx, game->exit_i, x * IMG, y * IMG);
			x++;
		}
		y++;
	}
}

void	load_player(t_complete *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == PLAYER)
				mlx_image_to_window(game->mlx, game->player_i, x * IMG,
					y * IMG);
			x++;
		}
		y++;
	}
}
