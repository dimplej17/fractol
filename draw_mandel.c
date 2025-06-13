/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:21:57 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/12 20:28:15 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_pixel_iter(double c_real, double c_imag, double a, double b)
{
	double	a_squared;
	double	b_squared;
	double	atemp;
	int		iter;

	iter = 0;
	while (iter < MAX_ITER)
	{
		a_squared = a * a;
		b_squared = b * b;
		if (a_squared + b_squared > 4)
			break ;
		atemp = a_squared - b_squared + c_real;
		b = 2 * a * b + c_imag;
		a = atemp;
		iter++;
	}
	return (iter);
}

void	compute_and_draw_mandel(t_fractal *f, int px)
{
	int		py;
	double	c_real;
	double	c_imag;
	int		iter;

	py = 0;
	while (py < HEIGHT)
	{
		c_real = f->min_real + ((double)px / WIDTH) * (f->max_real - f->min_real);
		c_imag = f->min_imag + ((double)py / HEIGHT) * (f->max_imag - f->min_imag);
		iter = mandelbrot_pixel_iter(c_real, c_imag, 0, 0);
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
		compute_and_draw_mandel(fractal, px);
		px++;
	}
}

void	draw_fractal(t_fractal *fractal)
{
	if (fractal->fractal_type == 0)
		draw_mandelbrot(fractal);
	else
		draw_julia(fractal);
}
