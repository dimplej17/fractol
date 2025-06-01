#include "fractol.h"

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(img, x, y, color);
}

int	get_color(int iter)
{
	if (iter == MAX_ITER)
		return (0x000000FF);         // black for inside
	return (0xFFFFFF - iter * 1000); // gradient
}