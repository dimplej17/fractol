#include "fractol.h"

int	mandelbrot_pixel_iter(double a, double b)
{
	double	x;
	double	y;
	double	x_squared;
	double	y_squared;
	double	xtemp;
	int		iter;

	x = 0.0;
	y = 0.0;
	iter = 0;
	while (iter < MAX_ITER)
	{
		x_squared = x * x;
		y_squared = y * y;
		if (x_squared + y_squared > 4)
			break ;
		xtemp = x_squared - y_squared + a;
		y = 2 * x * y + b;
		x = xtemp;
		iter++;
	}
	return (iter);
}

void	compute_and_draw_row(t_fractal *f, int px)
{
	int		py;
	double	a;
	double	b;
	int		iter;

	py = 0;
	while (py < HEIGHT)
	{
		a = f->min_real + ((double)px / WIDTH) * (f->max_real - f->min_real);
		b = f->min_imag + ((double)py / HEIGHT) * (f->max_imag - f->min_imag);
		iter = mandelbrot_pixel_iter(a, b);
		mlx_put_pixel(f->img, px, py, get_color(iter));
		py++;
	}
}

void	draw_mandelbrot(t_fractal *fractal)
{
	int	px;

	px = 0;
	while (px < WIDTH)
	{
		compute_and_draw_row(fractal, px);
		px++;
	}
}

void draw_fractal(t_fractal *fractal)
{
    if (fractal->fractal_type == 0)
        draw_mandelbrot(fractal);
    else
        draw_julia(fractal);
}
