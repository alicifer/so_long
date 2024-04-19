/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicifer <alicifer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:56:27 by alicifer          #+#    #+#             */
/*   Updated: 2024/04/18 14:53:25 by alicifer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "my_libft/libft.h"

# define IMG			64
# define WALL				'1'
# define FLOOR 				'0'
# define COLLECT  			'C'
# define PLAYER				'P'
# define MAP_EXIT 		 	'E'

typedef enum e_move
{
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
}	t_move;

typedef struct s_complete
{
	int				fd;
	char			**map;
	int				map_height;
	int				map_width;
	int				player_count;
	int				move_count;
	int				collect_count;
	int				exit_count;
	int				exit_available;
	int				x_player;
	int				y_player;
	mlx_t			*mlx;
	mlx_image_t		*floor_i;
	mlx_image_t		*wall_i;
	mlx_image_t		*player_i;
	mlx_image_t		*exit_i;
	mlx_image_t		*collect_i;
	mlx_texture_t	*floor_t;
	mlx_texture_t	*wall_t;
	mlx_texture_t	*player_t;
	mlx_texture_t	*exit_t;
	mlx_texture_t	*collect_t;
}	t_complete;

t_complete	*init_game(void);
int			map_read(t_complete *game, char **argv);
int			add_line_map(t_complete *game, char *line);
int			ft_map_width(char *line);
int			check_walls(t_complete *game);
void		check_count_items(t_complete *game);
int			check_square(t_complete *game);
void		floodfill(t_complete *game, int x, int y);
void		find_position_player(t_complete *game);
int			check_floodfill(t_complete *game, char **argv);
int			check_map(t_complete *game, char **argv);
void		txt_to_game(t_complete *game);
void		load_imgs(t_complete *game);
void		check_move(t_complete *game, int dir, int y, int x);
void		print_error(char *msg, t_complete *game);
void		free_map_txt(t_complete *game);
void		free_mat(char **mat);
void		free_all(t_complete	*game);
void		move_player(t_complete *game, int dir);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		reload_player(t_complete *game);
void		check_exit_move(t_complete *game, int dir);
void		load_player(t_complete *game);
void		read_while(t_complete *game, char *line);

#endif