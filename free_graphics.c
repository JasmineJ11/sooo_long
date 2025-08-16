
#include "so_long.h"


void	free_all_textures(mlx_texture_t *t1, mlx_texture_t *t2,
		mlx_texture_t *t3, mlx_texture_t *t4, mlx_texture_t *t5)
{
	if (t1)
		mlx_delete_texture(t1);
	if (t2)
		mlx_delete_texture(t2);
	if (t3)
		mlx_delete_texture(t3);
	if (t4)
		mlx_delete_texture(t4);
	if (t5)
		mlx_delete_texture(t5);
}

void free_graphics(t_graphics **graphics)
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