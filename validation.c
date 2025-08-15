/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:55:58 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/15 16:33:22 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"





static void element_counts(t_parameter_check *checker)
{
   if(checker->entrance  != 1)
	   exit_prog(NULL, NULL, NULL, "Map need 1 player.");
   if(checker->collectible <= 0)
	   exit_prog(NULL, NULL, NULL, "Map need at least 1 collectible.");
   if(checker->exit != 1)
	   exit_prog(NULL, NULL, NULL, "Map need 1 exit.");
}

static void element_process(char **parameter, t_parameter_check *checker, int i, int j)
{
   if (parameter[i][j] != '1' && parameter[i][j] != '0'
	   && parameter[i][j] != 'C' && parameter[i][j] != 'E'
	   && parameter[i][j] != 'P')
	   exit_prog(&parameter, NULL, NULL, "Illegal element in map.");
   if ((i == 0 || i == checker->height - 1 || j == 0 || j == checker->length - 1)
	   && parameter[i][j] != '1')
	   exit_prog(&parameter, NULL, NULL, "Map should be surrounded by walllls");
	if (parameter[i][j] == 'C')
		checker->collectible++;
	if (parameter[i][j] == 'E')
		checker->exit++;
	if (parameter[i][j] == 'P')
		checker->entrance++;
	
}

static void content(char **parameter,  t_parameter_check *checker)
{
	int i;
	int j;

	checker->collectible = 0;
	checker->entrance = 0;
	checker->exit = 0;

	i = 0;
	while(i < checker->height)
	{
		j = 0;
		while(j < checker->length)
		{
			element_process(parameter, checker, i, j);
			j++;
		}
		i++;
	}
}

static void dimensions(char **parameter, t_parameter_check *checker)
{
	int i;
	int len;
	
	checker->height = arr_len(parameter);
	checker->length = ft_strlen(parameter[0]);
   if(checker->height > 130 || checker->length > 130)
	   exit_prog(&parameter, NULL, NULL, "Map dimensions too large (max 130x130).");
   if(checker->height < 3 || checker->length < 3)
	   exit_prog(&parameter, NULL, NULL, "Map too small.");
		
	i = 0;
	while(i < checker->height)
	{
		len = ft_strlen(parameter[i]);
	   if(len == 0)
		   exit_prog(&parameter, NULL, NULL, "Map has empty line.");
	   if(len != checker->length)
		   exit_prog(&parameter, NULL, NULL, "Map is wrong wrong shape.");
		i++;
	}
}

t_parameter_check	validate_parameter(char **parameter)
{
	t_parameter_check	checker;

	dimensions(parameter, &checker);
	content(parameter, &checker);
	element_counts(&checker);
	
	return checker;
}