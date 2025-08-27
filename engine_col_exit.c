/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_col_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:26:58 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/27 20:51:47 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ini_exit_ins(t_game *game, int x, int y)
{
	int32_t	exit_id;

	exit_id = image_to_window(game, game->graphics->img_exit, x * 64, y * 64);
	game->graphics->img_exit->instances[exit_id].enabled = false;
	game->graphics->exit_ins_id = exit_id;
}

static void	ini_col_ins(t_game *game, int x, int y, int *ids)
{
	int32_t	insids;

	insids = image_to_window(game, game->graphics->img_collectible,
			x * 64, y * 64);
	game->graphics->img_collectible->instances[insids].enabled = false;
	game->collect_ins_ids[*ids] = insids;
	(*ids)++;
}

static void	show_first(t_game *game, mlx_instance_t *col_inx)
{
	if (game->total_collectible > 0)
		col_inx[game->collect_ins_ids[0]].enabled = true;
}

void	ini_col_exit_insids(t_game *game)
{
	int				ids;
	int				y;
	int				x;
	t_tile			*tile;
	mlx_instance_t	*col_inx;

	ids = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->length)
		{
			tile = &game->board[y][x];
			if (tile->is_collectible)
				ini_col_ins(game, x, y, &ids);
			if (tile->is_exit)
				ini_exit_ins(game, x, y);
			x++;
		}
		y++;
	}
	col_inx = game->graphics->img_collectible->instances;
	shuffle_array(col_inx, game->total_collectible);
	show_first(game, col_inx);
}
