/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_game_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:40:29 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/19 09:19:00 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

static void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->length || y >= game->height
		|| game->board[y][x].type == TILE_WALL
		|| game->board[y][x].is_visited)
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

