/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:10:03 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/16 14:20:28 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
static const char *cat_lines[] = {
    "In the wind, I hear a voice… gentle and familiar, as if calling your name. Perhaps it was the embrace where everything began. There are more answers ahead. Don’t stop now.",
    "Your footsteps sound lonely. Do you remember the laughter of those who once walked beside you? Keep going forward… another echo may await you.",
    "Some gazes were fleeting, yet they lit your night like stars. Are you still chasing that light...",
    "Deep along the path, a running figure fades into the distance. Was that the dream you left behind in the horizon? ",
    "You have walked so far, yet something still feels missing. Lift your head… do you see me? I am not far from you. Take one more step… and you will understand."
};

bool move_player(t_game *game, int dx, int dy)
{
    int nx = game->player->x + dx;
    int ny = game->player->y + dy;
    if (nx < 0 || nx >= game->length || ny < 0 || ny >= game->height)
        return false;
    t_tile *tile = &game->board[ny][nx];
    if (tile->type == TILE_WALL)
        return false; 
    // 收集物
    if (tile->is_collectible && !tile->is_collected)
    {
        tile->is_collected = true;
        ft_putstr_fd((char *)cat_lines[game->player->has_collectible], 1);
        ft_putstr_fd("\n", 1);
        game->player->has_collectible++;
    }
    // 只有收集完所有收集物并到达出口才退出
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
