/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:10:03 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/22 15:44:00 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	cat_lines(t_game *game, int idx)
{
	char *const	lines[] = {"Shhh… somewhere in the Milky Way, I hear\
a voice… gentle and familiar,\
as if calling your name. Perhaps it was the embrace where everything began.\
Come to me...", "Every step you take… it sounds so lonely. \
Do you still remember the laughter we shared? \
I’ve been waiting for you for so long.", \
"Some gazes passed like whispers… yet they lit your night like stars. \
Can you feel me there? Come… are you still chasing that light?", \
"Far along the path… a fleeting figure fades into the distance. \
That dream you left behind? It’s me. Follow… you’ll find me on the \
horizon.", "You’ve traveled so far, \
and yet a part of you still feels empty. One more step,\
lift your head… do you see me? I’m here,\
with my whole heart, loving you,always."};

	if (idx >= 5)
		ft_putstr_fd((char *)lines[4], 1);
	else if (idx == game->total_collectible - 1)
		ft_putstr_fd((char *)lines[4], 1);
	else
		ft_putstr_fd((char *)lines[idx], 1);
}

static void	if_exit(t_game *game, t_tile *tile)
{
	mlx_instance_t	*col_inx;

	col_inx = game->graphics->img_exit->instances;
	if (game->player->has_collectible == game->total_collectible)
		col_inx[game->graphics->exit_ins_id].enabled = true;
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
	mlx_instance_t	*col_ins;

	p_col = game->player->has_collectible;
	col_ins = game->graphics->img_collectible->instances;
	if (p_col != game->total_collectible && tile->is_collectible
		&& !tile->is_collected && col_ins[p_col].x == nx * 64
		&& col_ins[p_col].y == ny * 64)
	{
		tile->is_collected = true;
		if (p_col < game->total_collectible)
			col_ins[p_col].enabled = false;
		if (p_col + 1 < game->total_collectible)
			col_ins[p_col + 1].enabled = true;
		cat_lines(game, p_col);
		ft_putstr_fd("\n", 1);
		game->player->has_collectible++;
	}
	if_exit(game, tile);
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
	collect_ins(game, tile, nx, ny);
	return (true);
}
