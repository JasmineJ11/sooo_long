/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:10:03 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/18 17:01:34 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
static const char *cat_lines[] = {
    "Shhh, in the wind, I hear a voice… gentle and familiar, as if calling your name. Perhaps it was the embrace where everything began. Come to me...",
    "Your footsteps sound lonely. Do you remember the laughter of us? Keep going forward…",
    "Some gazes passed like whispers, yet they lit your night like stars. Are you still chasing that light?",
    "Deep along the path, a fleeting figure fades into the distance. Was that our dream you once left behind on the horizon?",
    "You have walked so far, yet something still feels missing. Lift your head… do you see me?"
};


void    collect_ins(t_game *game, t_tile *tile, int nx, int ny)
{
    int idx = game->player->has_collectible;
    int insid = game->collect_ins_ids[idx];
    
    
    if (tile->is_collectible && !tile->is_collected && game->graphics->img_collectible->instances[insid].x == nx * 64 &&
    game->graphics->img_collectible->instances[insid].y == ny * 64)
    {
        tile->is_collected = true;
        // 隐藏当前收集物实例
        if (idx < game->total_collectible)
            game->graphics->img_collectible->instances[game->collect_ins_ids[idx]].enabled = false;
        // 显示下一个收集物实例
        if (idx + 1 < game->total_collectible)
            game->graphics->img_collectible->instances[game->collect_ins_ids[idx + 1]].enabled = true;
            
        ft_putstr_fd((char *)cat_lines[idx], 1);
        ft_putstr_fd("\n", 1);
        //__builtin_printf("has_collectible: %d\n", game->player->has_collectible);
        game->player->has_collectible++;
    }
    // 收集完所有收集物后显示出口
    if (game->player->has_collectible == game->total_collectible)
    {
        game->graphics->img_exit->instances[game->graphics->exit_ins_id].enabled = true;
    }
    // 只有收集完所有收集物并到达出口才退出
    if (tile->is_exit && game->player->has_collectible == game->total_collectible)
    {
        game->is_won = true;
        exit_prog(NULL, &game, &(game->graphics), NULL);
    }
}

void    move_player_ins(mlx_image_t *player, int nx, int ny)
{
    player->instances->x = nx * 64;
    player->instances->y = ny * 64;
    
}

bool move_player(t_game *game, int dx, int dy)
{
    int nx = game->player->x + dx;
    int ny = game->player->y + dy;
    if (nx < 0 || nx >= game->length || ny < 0 || ny >= game->height)
        return false;
    t_tile *tile = &game->board[ny][nx];
    if (tile->type == TILE_WALL)
        return false; 
   
    
    game->player->x = nx;
    game->player->y = ny;
    move_player_ins(game->graphics->img_player, nx, ny);
    
    game->player->movements++;
    ft_putstr_fd("Steps taken: ", 1);
    ft_putnbr_fd(game->player->movements, 1);
    ft_putstr_fd("\n", 1);

     // 收集物
    collect_ins(game, tile, nx, ny);
    return true;
}
