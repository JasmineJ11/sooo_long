/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:20:48 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/22 17:22:59 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	shuffle_array(mlx_instance_t *col_inx, int length)
{
	unsigned int	random;
	int				i;
	int				j;
	mlx_instance_t	temp;

	random = (unsigned long)&random;
	i = length - 1;
	while (i > 0)
	{
		random = random * 1664525 + 1013904223;
		j = random % (i + 1);
		temp = col_inx[i];
		col_inx[i] = col_inx[j];
		col_inx[j] = temp;
		i--;
	}
}
