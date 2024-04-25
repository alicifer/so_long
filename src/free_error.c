/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:20:14 by alicifer          #+#    #+#             */
/*   Updated: 2024/04/18 13:31:37 by alicifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	print_error(char *msg, t_complete *game)
{
	free_all(game);
	ft_printf("%s\n", msg);
	exit (0);
}

void	free_map_txt(t_complete *game)
{
	if (game->collect_t)
		mlx_delete_texture(game->collect_t);
	if (game->floor_t)
		mlx_delete_texture(game->floor_t);
	if (game->wall_i)
		mlx_delete_texture(game->wall_t);
	if (game->player_t)
		mlx_delete_texture(game->player_t);
	if (game->exit_t)
		mlx_delete_texture(game->exit_t);
	if (game->exit_i)
		mlx_delete_image(game->mlx, game->exit_i);
	if (game->wall_i)
		mlx_delete_image(game->mlx, game->exit_i);
	if (game->floor_i)
		mlx_delete_image(game->mlx, game->exit_i);
	if (game->collect_i)
		mlx_delete_image(game->mlx, game->exit_i);
	if (game->player_i)
		mlx_delete_image(game->mlx, game->player_i);
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

void	free_all(t_complete	*game)
{
	if (game)
	{
		if (game->map)
			free_mat(game->map);
		if (game)
			free_map_txt(game);
		free(game);
	}
}
