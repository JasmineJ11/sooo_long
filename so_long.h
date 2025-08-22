/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:24:05 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/22 10:05:54 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>

// Tile types
typedef enum a_type
{
	TILE_WALL,
	TILE_EMPTY,
}					t_type;

// STRUCTS

typedef struct s_parameter_check
{
	int				length;
	int				height;
	int				entrance;
	int				exit;
	int				collectible;
}					t_parameter_check;

typedef struct s_tile
{
	t_type			type;
	int				x;
	int				y;
	bool			is_collectible;
	bool			is_exit;
	bool			is_visited;
	bool			is_collected;

}					t_tile;

typedef struct s_player
{
	int				x;
	int				y;
	int				has_collectible;
	int				movements;

}					t_player;

typedef struct s_graphics
{
	mlx_t			*mlx;
	mlx_image_t		*img_wall;
	mlx_image_t		*img_floor;
	mlx_image_t		*img_player;
	mlx_image_t		*img_collectible;
	mlx_image_t		*img_exit;
	int				exit_ins_id;
}					t_graphics;

typedef struct s_textures
{
	mlx_texture_t	*tw;
	mlx_texture_t	*tf;
	mlx_texture_t	*tp;
	mlx_texture_t	*tc;
	mlx_texture_t	*te;
}					t_textures;

typedef struct s_game
{
	int				length;
	int				height;
	t_tile			**board;
	t_player		*player;
	bool			is_won;
	t_graphics		*graphics;
	int				total_collectible;
	int				*collect_ins_ids;

}					t_game;

// ini_game.c
t_game				*create_game(t_parameter_check *checker, char **parameter);
bool				path_check(t_game *game);

// ini_game_helper.c
void				init_board_tiles(t_tile **board, t_parameter_check *checker,
						char **parameter, t_game *game);

// movement.c
bool				move_player(t_game *game, int dx, int dy);

// free.c
void				exit_prog(char ***parameter, t_game **game,
						t_graphics **graphics, char *msg);
void				free_parameter(char ***parameter);
void				free_game(t_game **game);
void				free_board(t_tile ***board, int height);

// free_graphics.c
void				free_all_textures(t_textures *textures);

void				free_graphics(t_graphics **graphics);

// so_long.c
void				close_fd_and_exit(int fd, char *msg);

// validation.c
t_parameter_check	validate_parameter(char **parameter);

// utils.c
int					arr_len(char **arr);

// engine.c
void				start_engine(t_game *game);

// engine_col_exit.c
void				ini_col_exit_insids(t_game *game);

#endif