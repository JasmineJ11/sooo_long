/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:11:30 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/18 15:09:53 by jiawli           ###   ########.fr       */
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

void	exit_prog(char ***parameter, t_game **game, t_graphics **graphics, char *msg)
{
	free_graphics(graphics);
	free_parameter(parameter);
	free_game(game);
	if (!msg)
	{
		printf("Hi, little kitten. You have wandered so far, searching for my voice, my shadow, and our dream you once left behind.\nBut haven’t you noticed? I was always here, waiting in the quiet corners of your heart.\nWe were never apart.\nNice to meet you ˚> 𖥦 <)/♡\n");
		exit(EXIT_SUCCESS);
	}
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}