/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:28:06 by alicifer          #+#    #+#             */
/*   Updated: 2024/04/19 11:14:36 by alicifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	my_keyhook(mlx_key_data_t keydata, void *game)
{
	t_complete	*temp;

	temp = game;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		check_move(temp, UP, temp->y_player - 1, temp->x_player);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		check_move(temp, DOWN, temp->y_player + 1, temp->x_player);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		check_move(temp, RIGHT, temp->y_player, temp->x_player + 1);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		check_move(temp, LEFT, temp->y_player, temp->x_player - 1);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_all(temp);
		exit (0);
	}
}

void	check_move(t_complete *game, int dir, int y, int x)
{
	if (y < game->map_height && x < game->map_width && y >= 0 && x >= 0)
	{
		if (game->map[y][x] != WALL)
		{
			if (game->map[y][x] == COLLECT)
			{
				game->map[y][x] = FLOOR;
				game->collect_count--;
				if (mlx_image_to_window(game->mlx,
						game->floor_i, x * IMG, y * IMG) < 0)
					print_error("Error rendering floor.", game);
				if (game->collect_count == 0)
					game->exit_available = 1;
				reload_player(game);
				move_player(game, dir);
			}
			else if (game->map[y][x] == MAP_EXIT)
				check_exit_move(game, dir);
			else
				move_player(game, dir);
		}
	}
}

void	check_exit_move(t_complete *game, int dir)
{
	if (game->collect_count == 0)
	{
		move_player(game, dir);
		print_error("You win. All collectible reached!!", game);
		free_all(game);
	}
}

void	move_player(t_complete *game, int dir)
{
	game->map[game->y_player][game->x_player] = FLOOR;
	if (dir == UP)
	{
		game->y_player--;
		(game->player_i)->instances[0].y -= IMG;
	}
	if (dir == RIGHT)
	{
		game->x_player++;
		(game->player_i)->instances[0].x += IMG;
	}
	if (dir == DOWN)
	{
		game->y_player++;
		(game->player_i)->instances[0].y += IMG;
	}
	if (dir == LEFT)
	{
		game->x_player--;
		(game->player_i)->instances[0].x -= IMG;
	}
	game->map[game->y_player][game->x_player] = PLAYER;
	game->move_count++;
	ft_printf("Moves %d\n", game->move_count);
}

void	reload_player(t_complete *game)
{
	mlx_delete_texture(game->player_t);
	mlx_delete_image(game->mlx, game->player_i);
	game->player_t = mlx_load_png("./sprites/player.png");
	game->player_i = mlx_texture_to_image(game->mlx, game->player_t);
	if (!game->player_i)
		return ;
	mlx_image_to_window(game->mlx, game->player_i,
		game->x_player * 64, game->y_player * 64);
}
