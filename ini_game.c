/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:36:28 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/18 10:42:59 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void init_tile(t_tile *tile, int x, int y, char map_char)
{
    tile->type = (map_char == '1') ? TILE_WALL : TILE_EMPTY;
    tile->x = x;
    tile->y = y;
    tile->is_collectible = (map_char == 'C');
    tile->is_exit = (map_char == 'E');
    tile->is_visited = false;
    tile->is_collected = false;
}

static void init_board_tiles(t_tile **board, t_parameter_check *checker, char **parameter, t_game *game)
{
    int y = 0;
    int x;
    
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

static t_tile **allocate_board(t_parameter_check *checker, char ***parameter, t_game **game)
{
    t_tile **board;
    int y = 0;
    
    board = malloc(sizeof(t_tile*) * checker->height);
    if (!board)
        exit_prog(parameter, game, NULL, "Memory allocation failed: board rows.");
    
    while (y < checker->height)
    {
        board[y] = malloc(sizeof(t_tile) * checker->length);
        if (!board[y])
        {
            free_board(&board, y);
            exit_prog(parameter, game, NULL, "Memory allocation failed: board columns.");
        }
        y++;
    }
    return board;
}

static t_tile **create_board(t_parameter_check *checker, char **parameter, t_game *game)
{
    t_tile **board;
    
    board = allocate_board(checker, &parameter, &game);
    init_board_tiles(board, checker, parameter, game);
    return board;
}

static t_player *create_player(char **parameter, t_game *game)
{
    t_player *player;
    
    player = malloc(sizeof(t_player));
    if (!player)
        exit_prog(&parameter, &game, NULL, "Memory allocation failed: player creation.");
    
    player->x = 0;
    player->y = 0;
    player->has_collectible = 0;
    player->movements = 0;

    return player;
}

t_game *create_game(t_parameter_check *checker, char **parameter)
{
    t_game *game;
    
    game = malloc(sizeof(t_game));
    if (!game)
        exit_prog(&parameter, NULL, NULL, "Memory allocation failed: game creation.");
    
    game->length = checker->length;
    game->height = checker->height;
    game->total_collectible = checker->collectible;
    game->player = create_player(parameter, game);
    game->board = create_board(checker, parameter, game);
    game->is_won = false;
    game->graphics = NULL;
    game->collect_ins_ids = NULL;

    return game;
}
