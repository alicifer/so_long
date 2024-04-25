/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:14:31 by alicifer          #+#    #+#             */
/*   Updated: 2024/04/18 13:30:50 by alicifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_map_width(char *line)
{
	int	width;

	width = 0;
	while (line[width] != '\0')
		width++;
	if (line[width - 1] == '\n')
		width--;
	return (width);
}

void	read_while(t_complete *game, char *line)
{
	int		i;

	i = 1;
	while (line != NULL)
	{
		if (i > 100)
			print_error ("I´m sorry your map is so_long!", game);
		game->map[i] = ft_strdup(line);
		if (!game->map[i])
			print_error("Memory allocation error", game);
		free(line);
		line = get_next_line(game->fd);
		i++;
	}
	game->map[i] = NULL;
	game->map_height = i;
}

int	map_read(t_complete *game, char **argv)
{
	char	*readmap;

	game->fd = open(argv[1], O_RDONLY);
	if (game->fd == -1)
		print_error("Failed to open map file", game);
	game->map = (char **)malloc(sizeof(char *) * 100);
	if (!game->map)
		print_error("Memory allocation error", game);
	readmap = get_next_line(game->fd);
	if (!readmap)
		print_error("Empty map", game);
	game->map[0] = ft_strdup(readmap);
	if (!game->map[0])
		print_error("Memory allocation error", game);
	free (readmap);
	readmap = get_next_line(game->fd);
	read_while(game, readmap);
	return (1);
}

void	find_position_player(t_complete *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width && game->map[y][x] != '\0')
		{
			if (game->map[y][x] == PLAYER)
			{
				game->x_player = x;
				game->y_player = y;
				return ;
			}
			x++;
		}
		y++;
	}
	return ;
}

int	check_walls(t_complete *game)
{
	int	x;
	int	y;

	x = 0;
	ft_map_width(game->map[0]);
	while (x < game->map_width)
	{
		if (game->map[0][x] != WALL
			|| game->map[game->map_height - 1][x] != WALL)
			return (0);
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != WALL
			|| game->map[y][game->map_width - 1] != WALL)
			return (0);
		y++;
	}
	return (1);
}
