/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:37:34 by alicifer          #+#    #+#             */
/*   Updated: 2024/04/18 13:32:25 by alicifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_complete	*init_game(void)
{
	t_complete	*game;

	game = (t_complete *)ft_calloc(1, sizeof(t_complete));
	if (!game)
		print_error("Error while allocating memory", game);
	return (game);
}

int	main(int argc, char **argv)
{
	t_complete	*game;

	game = init_game();
	if (!game)
		print_error("Game allocation memory failed", game);
	if (argc != 2)
		print_error("Incorrect number of arguments.", game);
	map_read(game, argv);
	if (check_map(game, argv) == 0)
	{
		txt_to_game(game);
		load_imgs(game);
		load_player(game);
	}
	mlx_key_hook(game->mlx, &my_keyhook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free(game);
	return (0);
}
