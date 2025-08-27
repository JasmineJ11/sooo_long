/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:45:04 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/27 20:53:51 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ini_wfp_on_window(t_game *game)
{
	int		y;
	int		x;
	t_tile	*tile;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->length)
		{
			tile = &game->board[y][x];
			if (tile->type == TILE_WALL)
				image_to_window(game, game->graphics->img_wall, x * 64, y * 64);
			else
			{
				image_to_window(game, game->graphics->img_floor,
					x * 64, y * 64);
			}
			x++;
		}
		y++;
	}
	image_to_window(game, game->graphics->img_player,
		game->player->x * 64, game->player->y * 64);
}

static void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		dx;
	int		dy;

	game = (t_game *)param;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
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
		exit_prog(NULL, &game, &(game->graphics), "Don't Escape > <\n");
}

static bool	texture_to_image(t_game *game, t_textures *textures)
{
	game->graphics->img_wall = mlx_texture_to_image(game->graphics->mlx,
			textures->tw);
	game->graphics->img_floor = mlx_texture_to_image(game->graphics->mlx,
			textures->tf);
	game->graphics->img_player = mlx_texture_to_image(game->graphics->mlx,
			textures->tp);
	game->graphics->img_collectible = mlx_texture_to_image(game->graphics->mlx,
			textures->tc);
	game->graphics->img_exit = mlx_texture_to_image(game->graphics->mlx,
			textures->te);
	free_all_textures(textures);
	return (game->graphics->img_wall && game->graphics->img_floor
		&& game->graphics->img_player && game->graphics->img_collectible
		&& game->graphics->img_exit);
}

static bool	init_mlx_and_images(t_game *game)
{
	t_textures	*trs;

	trs = ft_calloc(1, sizeof(t_textures));
	if (!trs)
		exit_prog(NULL, &game, &(game->graphics), "textures malloc fail.");
	trs->tw = mlx_load_png("texture/wall.png");
	trs->tf = mlx_load_png("texture/floor.png");
	trs->tp = mlx_load_png("texture/player.png");
	trs->tc = mlx_load_png("texture/collect.png");
	trs->te = mlx_load_png("texture/exit.png");
	if (!trs->tw || !trs->tf || !trs->tp || !trs->tc || !trs->te)
	{
		free_all_textures(trs);
		return (false);
	}
	game->graphics->mlx = mlx_init(game->length * 64, game->height * 64,
			"MissaKissa", false);
	if (!game->graphics->mlx)
	{
		free_all_textures(trs);
		return (false);
	}
	return (texture_to_image(game, trs));
}

void	start_engine(t_game *game)
{
	game->graphics = ft_calloc(1, sizeof(t_graphics));
	if (!game->graphics)
		exit_prog(NULL, &game, NULL, "Graphics, Mem fail.");
	if (!init_mlx_and_images(game))
	{
		exit_prog(NULL, &game, &(game->graphics), "Ini MLX engine fail");
		return ;
	}
	ini_wfp_on_window(game);
	ft_putstr_fd("Hi,little kitten. Why are you crying? Have you seen me?\n",
		1);
	ft_putstr_fd("The stars will light the path of your dreams.\n", 1);
	game->collect_ins_ids = calloc(1, sizeof(int) * game->total_collectible);
	if (!game->collect_ins_ids)
		exit_prog(NULL, &game, &(game->graphics), "Collect_ins_ids, Mem fail");
	ini_col_exit_insids(game);
	mlx_key_hook(game->graphics->mlx, key_callback, game);
	mlx_loop(game->graphics->mlx);
}
