/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:24:05 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/16 16:59:57 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "MLX42/MLX42.h"



// ========================================================================

// ========================================================================

// Tile types
typedef enum a_type
{
    TILE_WALL,
    TILE_EMPTY,
}				t_type;





// STRUCTS (按依赖顺序排列)

// Map validation results
typedef struct s_parameter_check
{
    int			length;
    int			height;
    int			entrance;
    int			exit;
    int			collectible;
}				t_parameter_check;



// Individual tile information (必须在 t_game 之前定义)
typedef struct s_tile
{
    t_type		type;
    int			x;
    int			y;
    bool		is_collectible;
    bool		is_exit;
    bool		is_visited;
    bool		is_collected;

}				t_tile;

// Player information (必须在 t_game 之前定义)
typedef struct s_player
{
    int			x;
    int			y;
    int			has_collectible;
    int			movements;

}				t_player;

// Graphics structure
typedef struct s_graphics
{
    mlx_t        *mlx;
    mlx_image_t  *img_wall;
    mlx_image_t  *img_floor; 
    mlx_image_t  *img_player;
    mlx_image_t  *img_collectible;
    mlx_image_t  *img_exit;
} t_graphics;


/*
mlx_image_to_window(mlx, img_player)
img_player->instances->x = 42;

mlx_image_t *image =  ??? 
int instance_number = mlx_image_to_window(mlx, image);
image->instances[instance_number].x = 42;
image->instances[instance_number].enabled = false;

*/



// Main game structure (可以引用 t_tile 和 t_player)
typedef struct s_game
{
    int				length;
    int				height;
    int				total_collectible;
    t_tile			**board;            
    t_player		*player;            
    bool		    is_won;
    t_graphics      *graphics;
    
}				t_game;


// Point structure
typedef struct s_point
{
    int			x;
    int			y;
}				t_point;





// ========================================================================
// FUNCTION DECLARATIONS
// ========================================================================

// ini_game.c 
t_game			*create_game(t_parameter_check *checker, char **parameter);
bool			path_check(t_game *game);

// movement.c
bool            move_player(t_game *game, int dx, int dy);



// free.c
void			exit_prog(char ***parameter, t_game **game, t_graphics **graphics, char *msg);
void			free_parameter(char ***parameter);
void			free_game(t_game **game);
void			free_board(t_tile ***board, int height);

//free_graphics.c
void	free_all_textures(mlx_texture_t *t1, mlx_texture_t *t2,
		mlx_texture_t *t3, mlx_texture_t *t4, mlx_texture_t *t5);
void            free_graphics(t_graphics **graphics);



// so_long.c
void			close_fd_and_exit(int fd, char *msg);

// validation.c
t_parameter_check	validate_parameter(char **parameter);

// utils.c
int				arr_len(char **arr);


// engine.c
void start_engine(t_game *game);



#endif