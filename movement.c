/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:10:03 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/15 16:31:42 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


bool move_player(t_game *game, int dx, int dy)
{
    int nx = game->player->x + dx;
    int ny = game->player->y + dy;
    // 边界判断
    if (nx < 0 || nx >= game->length || ny < 0 || ny >= game->height)
        return false;
    t_tile *tile = &game->board[ny][nx];
    if (tile->type == TILE_WALL)
        return false; 
    // 收集物
    if (tile->is_collectible)
    {
        tile->is_collectible = false;
        game->player->has_collectible++;
        // 加分数、隐藏图片
    }
    // 出口
    if (tile->is_exit && game->player->has_collectible == game->total_collectible)
    {
        game->is_won = true;
        exit_prog(NULL, &game, &(game->graphics), NULL);
    }
    game->player->x = nx;
    game->player->y = ny;
    game->player->movements++;
    ft_putstr_fd("Steps taken: ", 1);
    ft_putnbr_fd(game->player->movements, 1);
    ft_putstr_fd("\n", 1);
    return true;
}
