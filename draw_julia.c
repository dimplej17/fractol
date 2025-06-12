#include "fractol.h"

int	julia_pixel_iter(double x, double y, double c_real, double c_imag)
{
	double	x_squared;
	double	y_squared;
	double	xtemp;
	int		iter;

	iter = 0;
	while (iter < MAX_ITER)
	{
		x_squared = x * x;
		y_squared = y * y;
		if (x_squared + y_squared > 4)
			break ;
		xtemp = x_squared - y_squared + c_real;
		y = 2 * x * y + c_imag;
		x = xtemp;
		iter++;
	}
	return (iter);
}

void	compute_and_draw_julia_row(t_fractal *f, int px)
{
	int		py;
	double	x;
	double	y;
	int		iter;

	py = 0;
	while (py < HEIGHT)
	{
		x = f->min_real + ((double)px / WIDTH) * (f->max_real - f->min_real);
		y = f->min_imag + ((double)py / HEIGHT) * (f->max_imag - f->min_imag);
		iter = julia_pixel_iter(x, y, f->julia_real, f->julia_imag);
		mlx_put_pixel(f->img, px, py, get_color(iter));
		py++;
	}
}

void	draw_julia(t_fractal *fractal)
{
	int	px;

	px = 0;
	while (px < WIDTH)
	{
		compute_and_draw_julia_row(fractal, px);
		px++;
	}
}
