/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:45:04 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/15 16:38:49 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



// 显示地图和玩家
static void	show_instances_on_window(t_game *game)
{
	t_tile	*tile;

	for (int y = 0; y < game->height; y++)
	{
		for (int x = 0; x < game->length; x++)
		{
			tile = &game->board[y][x];
			if (tile->type == TILE_WALL)
				mlx_image_to_window(game->graphics->mlx, game->graphics->img_wall, x * 64, y * 64);
			else
				mlx_image_to_window(game->graphics->mlx, game->graphics->img_floor, x * 64, y * 64);
			// 显示未被收集的收集物
			if (tile->is_collectible)
				mlx_image_to_window(game->graphics->mlx, game->graphics->img_collectible, x * 64, y * 64);
			// 在胜利条件满足时显示出口
			if (tile->is_exit && game->player->has_collectible == game->total_collectible)
				mlx_image_to_window(game->graphics->mlx, game->graphics->img_exit, x * 64, y * 64);
		}
	}
	// 显示玩家
	mlx_image_to_window(game->graphics->mlx, game->graphics->img_player, game->player->x * 64,
		game->player->y * 64);
}


static void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		dx;
	int		dy;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		dx = 0;
		dy = 0;
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			dy = -1;
		if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			dy = 1;
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			dx = -1;
		if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			dx = 1;
		if (dx != 0 || dy != 0)
		{
			move_player(game, dx, dy);      // 负责移动和合法性判断
			show_instances_on_window(game); // 重新绘制
		}
	}
	if (keydata.key == MLX_KEY_ESCAPE)
   		exit_prog(NULL, &game, &(game->graphics), "Game window closed X.x\n");
	
}





// 初始化 MLX42 和图片
static bool	init_mlx_and_images(t_game *game)
{
    game->graphics->mlx = mlx_init(game->length * 64, game->height * 64, "so_long", false);
    if (!game->graphics->mlx)
        return false;
    game->graphics->img_wall = mlx_texture_to_image(game->graphics->mlx, mlx_load_png("assets/wall.png"));
    game->graphics->img_floor = mlx_texture_to_image(game->graphics->mlx, mlx_load_png("assets/floor.png"));
    game->graphics->img_player = mlx_texture_to_image(game->graphics->mlx, mlx_load_png("assets/player.png"));
    game->graphics->img_collectible = mlx_texture_to_image(game->graphics->mlx, mlx_load_png("assets/collect.png"));
    game->graphics->img_exit = mlx_texture_to_image(game->graphics->mlx, mlx_load_png("assets/exit.png"));
    if (!game->graphics->img_wall || !game->graphics->img_floor || !game->graphics->img_player
        || !game->graphics->img_collectible || !game->graphics->img_exit)
        return false;
    return true;
}


void	start_engine(t_game *game)
{
   if (!init_mlx_and_images(game))
   {
	   exit_prog(NULL, &game, &(game->graphics), "Failed to initialize MLX engine");
	   return ;
   }
	show_instances_on_window(game);
	mlx_key_hook(game->graphics->mlx, key_callback, game);
	mlx_loop(game->graphics->mlx);
}