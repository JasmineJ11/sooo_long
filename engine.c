/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:45:04 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/19 13:30:36 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void	show_collect_on_window(t_game *game)
// {
// 	t_tile	*tile;
// 	int		shown;
// 	int		y;
// 	int		x;

// 	shown = 0;
// 	y = 0;
// 	while (y < game->height)
// 	{
// 		x = 0;
// 		while (x < game->length)
// 		{
// 			tile = &game->board[y][x]; // 只显示第一个未被收集的收集物
// 			if (tile->is_collectible && !tile->is_collected && shown == 0)
// 			{
// 				mlx_image_to_window(game->graphics->mlx,
// 					game->graphics->img_collectible, x * 64, y * 64);
// 				shown = 1;
// 			}
// 			// 只有收集完所有收集物才显示出口
// 			if (tile->is_exit
// 				&& game->player->has_collectible == game->total_collectible)
// 				mlx_image_to_window(game->graphics->mlx,
// 					game->graphics->img_exit, x * 64, y * 64);
// 			x++;
// 		}
// 		y++;
// 	}
// }

static void	ini_exit_ins(t_game *game, int x, int y, t_tile *tile)
{
	int	exit_id;

	if (tile->is_exit)
	{
		exit_id = mlx_image_to_window(game->graphics->mlx,
				game->graphics->img_exit, x * 64, y * 64);
		game->graphics->img_exit->instances[exit_id].enabled = false;
		game->graphics->exit_ins_id = exit_id;
	}
}
static void	ini_col_ins(t_game *game, int x, int y, t_tile *tile,
		int *ids)
{
	int insids;
	if (tile->is_collectible)
	{
		insids = mlx_image_to_window(game->graphics->mlx,
				game->graphics->img_collectible, x * 64, y * 64);
		game->graphics->img_collectible->instances[insids].enabled = false;
		game->collect_ins_ids[*ids] = insids;
		(*ids)++;
	}
}
static void	ini_col_exit_insids(t_game *game)
{
	int		ids;
	int		y;
	int		x;
	t_tile	*tile;
	
	game->collect_ins_ids = malloc(sizeof(int) * game->total_collectible);
	ids = 0;
	
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->length)
		{
			tile = &game->board[y][x];
		
			ini_col_ins(game, x, y, tile, &ids);
			ini_exit_ins(game, x, y, tile);
			x++;
		}
		y++;
	}
	if (game->total_collectible > 0)
		game->graphics->img_collectible->instances[game->collect_ins_ids[0]].enabled = true;
}

static void	show_instances_on_window(t_game *game)
{
	int		y;
	int		x;
	t_tile	*tile;

	// 1.floor and wall first
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->length)
		{
			tile = &game->board[y][x];
			if (tile->type == TILE_WALL)
				mlx_image_to_window(game->graphics->mlx,
					game->graphics->img_wall, x * 64, y * 64);
			else
				mlx_image_to_window(game->graphics->mlx,
					game->graphics->img_floor, x * 64, y * 64);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->graphics->mlx, game->graphics->img_player,
		game->player->x * 64, game->player->y * 64);
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
			move_player(game, dx, dy);
	}
	if (keydata.key == MLX_KEY_ESCAPE)
		exit_prog(NULL, &game, &(game->graphics), "Close window > <\n");
}

static void	texture_to_image(t_game *game, mlx_texture_t *tw, mlx_texture_t *tf,
		mlx_texture_t *tp, mlx_texture_t *tc, mlx_texture_t *te)
{
	game->graphics->img_wall = mlx_texture_to_image(game->graphics->mlx, tw);
	game->graphics->img_floor = mlx_texture_to_image(game->graphics->mlx, tf);
	game->graphics->img_player = mlx_texture_to_image(game->graphics->mlx, tp);
	game->graphics->img_collectible = mlx_texture_to_image(game->graphics->mlx,
			tc);
	game->graphics->img_exit = mlx_texture_to_image(game->graphics->mlx, te);
	free_all_textures(tw, tf, tp, tc, te);
}

// 初始化 MLX42 和图片
static bool	init_mlx_and_images(t_game *game)
{
	mlx_texture_t	*tw;
	mlx_texture_t	*tf;
	mlx_texture_t	*tp;
	mlx_texture_t	*tc;
	mlx_texture_t	*te;

	tw = mlx_load_png("assets/wall.png");
	tf = mlx_load_png("assets/floor.png");
	tp = mlx_load_png("assets/player.png");
	tc = mlx_load_png("assets/collect.png");
	te = mlx_load_png("assets/exit.png");
	if (!tw || !tf || !tp || !tc || !te)
	{
		free_all_textures(tw, tf, tp, tc, te);
		return (false);
	}
	game->graphics->mlx = mlx_init(game->length * 64, game->height * 64,
			"MissaKissa", false);
	if (!game->graphics->mlx)
	{
		free_all_textures(tw, tf, tp, tc, te);
		return (false);
	}
	texture_to_image(game, tw, tf, tp, tc, te);
	return (game->graphics->img_wall && game->graphics->img_floor
		&& game->graphics->img_player && game->graphics->img_collectible
		&& game->graphics->img_exit);
}

void	start_engine(t_game *game)
{
	game->graphics = malloc(sizeof(t_graphics));
	if (!game->graphics)
		exit_prog(NULL, &game, NULL, "Memory allocation failed: graphics.");
	if (!init_mlx_and_images(game))
	{
		exit_prog(NULL, &game, &(game->graphics),
			"Failed to initialize MLX engine");
		return ;
	}
	show_instances_on_window(game);
	ft_putstr_fd("Hi,little kitten. Why are you crying? Have you seen me? The stars will light the path of your dreams.\n",
		1);
	ini_col_exit_insids(game);
	mlx_key_hook(game->graphics->mlx, key_callback, game);
	mlx_loop(game->graphics->mlx);
}
