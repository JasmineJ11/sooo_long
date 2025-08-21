/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_game_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:40:29 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/21 14:45:50 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->length || y >= game->height
		|| game->board[y][x].type == TILE_WALL || game->board[y][x].is_visited)
		return ;
	game->board[y][x].is_visited = true;
	flood_fill(game, x, y - 1);
	flood_fill(game, x, y + 1);
	flood_fill(game, x - 1, y);
	flood_fill(game, x + 1, y);
}

bool	path_check(t_game *game)
{
	int	i;
	int	j;

	flood_fill(game, game->player->x, game->player->y);
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->length)
		{
			if ((game->board[i][j].is_collectible || game->board[i][j].is_exit)
				&& !(game->board[i][j].is_visited))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static void	init_tile(t_tile *tile, int x, int y, char map_char)
{
	if (map_char == '1')
		tile->type = TILE_WALL;
	else
		tile->type = TILE_EMPTY;
	tile->x = x;
	tile->y = y;
	tile->is_collectible = (map_char == 'C');
	tile->is_exit = (map_char == 'E');
	tile->is_visited = false;
	tile->is_collected = false;
}

void	init_board_tiles(t_tile **board, t_parameter_check *checker,
		char **parameter, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < checker->height)
	{
		x = 0;
		while (x < checker->length)
		{
			init_tile(&board[y][x], x, y, parameter[y][x]);
			if (parameter[y][x] == 'P')
			{
				game->player->x = x;
				game->player->y = y;
			}
			x++;
		}
		y++;
	}
}
