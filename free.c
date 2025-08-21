/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:11:30 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/21 14:48:41 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_row(t_tile **row)
{
	if (row && *row)
	{
		free(*row);
		*row = NULL;
	}
}

void	free_board(t_tile ***board, int height)
{
	int	i;

	if (board && *board)
	{
		i = 0;
		while (i < height)
		{
			if ((*board)[i])
				free_row(&((*board)[i]));
			++i;
		}
		free(*board);
		*board = NULL;
	}
}

void	free_game(t_game **game)
{
	if (game && *game)
	{
		if ((*game)->player)
		{
			free((*game)->player);
			(*game)->player = NULL;
		}
		if ((*game)->collect_ins_ids)
		{
			free((*game)->collect_ins_ids);
			(*game)->collect_ins_ids = NULL;
		}
		free_board(&(*game)->board, (*game)->height);
		free(*game);
		*game = NULL;
	}
}

void	free_parameter(char ***parameter)
{
	int	i;

	if (parameter && *parameter)
	{
		i = 0;
		while ((*parameter)[i])
		{
			free((*parameter)[i]);
			(*parameter)[i] = NULL;
			i++;
		}
		free(*parameter);
		*parameter = NULL;
	}
}

void	exit_prog(char ***parameter, t_game **game, t_graphics **graphics,
		char *msg)
{
	free_graphics(graphics);
	free_parameter(parameter);
	free_game(game);
	if (!msg)
	{
		ft_putstr_fd("Hi, little kitten. Thank you…", 1);
		ft_putstr_fd("for finding me, after so long.\n", 1);
		ft_putstr_fd("You wandered so far…", 1);
		ft_putstr_fd("yet never left the place where I waited.\n", 1);
		ft_putstr_fd("We were never apart.\n", 1);
		ft_putstr_fd("I am You, and nice to meet you ˚> 𖥦 <)/♡\n", 1);
		exit(EXIT_SUCCESS);
	}
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	exit(EXIT_FAILURE);
}
