/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:10:03 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/19 15:09:50 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static const char	*cat_lines[] = {"Shhh… somewhere in the Milky Way, I hear a voice… gentle and familiar, as if calling your name. Perhaps it was the embrace where everything began. Come to me...",
		"Every step you take… it sounds so lonely. Do you still remember the laughter we shared? I’ve been waiting for you for so long.",
		"Some gazes passed like whispers… yet they lit your night like stars. Can you feel me there? Come… are you still chasing that light?",
		"Far along the path… a fleeting figure fades into the distance. That dream you left behind? It’s me. Follow… you’ll find me on the horizon.",
		"You’ve traveled so far, and yet a part of you still feels empty. One more step, lift your head… do you see me? I’m here, with my whole heart, loving you, always."};

static void if_exit(t_game *game, t_tile *tile, int p_col)
{
     // 收集完所有收集物后显示出口
	if (p_col == game->total_collectible)
		game->graphics->img_exit->instances[game->graphics->exit_ins_id].enabled = true;
	// 只有收集完所有收集物并到达出口才退出
	if (tile->is_exit
		&& game->player->has_collectible == game->total_collectible)
	{
		game->is_won = true;
		exit_prog(NULL, &game, &(game->graphics), NULL);
	}
}
        
static void	collect_ins(t_game *game, t_tile *tile, int nx, int ny)
{
	int				p_col;
	int				insid;
	mlx_instance_t	*col_ins;

	p_col = game->player->has_collectible;
	insid = game->collect_ins_ids[p_col];
	col_ins = game->graphics->img_collectible->instances;
	if (tile->is_collectible && !tile->is_collected && col_ins[insid].x == nx
		* 64 && col_ins[insid].y == ny * 64)
	{
		tile->is_collected = true;
		// 隐藏当前收集物实例
		if (p_col < game->total_collectible)
			col_ins[insid].enabled = false;
		// 显示下一个收集物实例
		if (p_col + 1 < game->total_collectible)
			col_ins[insid + 1].enabled = true;
		ft_putstr_fd((char *)cat_lines[p_col], 1);
		if (p_col >= 5)
			ft_putstr_fd((char *)cat_lines[4], 1);
		ft_putstr_fd("\n", 1);
		game->player->has_collectible++;
	}
    if_exit(game, tile, p_col);
}

void	move_player_ins(mlx_image_t *player, int nx, int ny)
{
	player->instances->x = nx * 64;
	player->instances->y = ny * 64;
}

bool	move_player(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	t_tile	*tile;

	nx = game->player->x + dx;
	ny = game->player->y + dy;
	if (nx < 0 || nx >= game->length || ny < 0 || ny >= game->height)
		return (false);
	tile = &game->board[ny][nx];
	if (tile->type == TILE_WALL)
		return (false);
	game->player->x = nx;
	game->player->y = ny;
	move_player_ins(game->graphics->img_player, nx, ny);
	game->player->movements++;
	ft_putstr_fd("Steps taken: ", 1);
	ft_putnbr_fd(game->player->movements, 1);
	ft_putstr_fd("\n", 1);
	// 收集物
	collect_ins(game, tile, nx, ny);
	return (true);
}
