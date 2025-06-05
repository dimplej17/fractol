#include "fractol.h"

void	draw_mandelbrot(t_data *data)
{
	double	cr;
	double	ci;
	double	zr;
	double	zi;
	int		iter;
	double	temp;
	int		y;
	int		x;

	zi = 0;
	zr = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cr = (x - WIDTH / 2.0) * 4.0 / WIDTH;
			ci = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
			zr = 0;
			zi = 0;
			iter = 0;
			while (zr * zr + zi * zi <= 4 && iter < MAX_ITER)
			{
				temp = zr * zr - zi * zi + cr;
				zi = 2 * zr * zi + ci;
				zr = temp;
				iter++;
			}
			put_pixel(data->img, x, y, get_color(iter));
			x++;
		}
		y++;
	}
}

void	draw_julia(t_data *data)
{
	double	zr;
	double	zi;
	int		iter;
	double	temp;
	int		y;
	int		x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
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
			x++;
		}
		y++;
	}
}
