#include "fractol.h"

void	draw_mandelbrot(t_data *data)
{
	double	cr;
	double	ci;
	double	zr;
	double	zi;
	int		iter;
	double	temp;

	zi = 0;
	zr = 0;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			cr = (x - WIDTH / 2.0) * 4.0 / WIDTH;
			ci = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
			zr = 0, zi = 0;
			iter = 0;
			while (zr * zr + zi * zi <= 4 && iter < MAX_ITER)
			{
				temp = zr * zr - zi * zi + cr;
				zi = 2 * zr * zi + ci;
				zr = temp;
				iter++;
			}
			put_pixel(data->img, x, y, get_color(iter));
		}
	}
}

void	draw_julia(t_data *data)
{
	double	zr;
	double	zi;
	int		iter;
	double	temp;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			zr = (x - WIDTH / 2.0) * 4.0 / WIDTH;
			zi = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
			iter = 0;
			while (zr * zr + zi * zi <= 4 && iter < MAX_ITER)
			{
				temp = zr * zr - zi * zi + data->julia_re;
				zi = 2 * zr * zi + data->julia_im;
				zr = temp;
				iter++;
			}
			put_pixel(data->img, x, y, get_color(iter));
		}
	}
}