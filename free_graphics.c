/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:44:56 by jiawli            #+#    #+#             */
/*   Updated: 2025/08/21 14:49:14 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_all_textures(t_textures *textures)
{
	if (textures->tw)
		mlx_delete_texture(textures->tw);
	if (textures->tf)
		mlx_delete_texture(textures->tf);
	if (textures->tp)
		mlx_delete_texture(textures->tp);
	if (textures->tc)
		mlx_delete_texture(textures->tc);
	if (textures->te)
		mlx_delete_texture(textures->te);
	free(textures);
}

void	free_graphics(t_graphics **graphics)
{
	if (graphics && *graphics)
	{
		if ((*graphics)->img_wall)
			mlx_delete_image((*graphics)->mlx, (*graphics)->img_wall);
		if ((*graphics)->img_floor)
			mlx_delete_image((*graphics)->mlx, (*graphics)->img_floor);
		if ((*graphics)->img_player)
			mlx_delete_image((*graphics)->mlx, (*graphics)->img_player);
		if ((*graphics)->img_collectible)
			mlx_delete_image((*graphics)->mlx, (*graphics)->img_collectible);
		if ((*graphics)->img_exit)
			mlx_delete_image((*graphics)->mlx, (*graphics)->img_exit);
		if ((*graphics)->mlx)
			mlx_terminate((*graphics)->mlx);
		free(*graphics);
		*graphics = NULL;
	}
}
