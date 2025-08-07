/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:11:30 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/07 14:37:08 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	exit_prog(char ***parameter, char *msg)
{
	free_parameter(parameter);
	if (!msg)
	{
		ft_printf("Game Over!\n");
		exit(EXIT_SUCCESS);
	}
	ft_printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
		
}