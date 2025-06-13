/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:21:50 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/12 20:34:44 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_pixel_iter(double z_real, double z_imag, double c_real, double c_imag)
{
	double	a_squared;
	double	b_squared;
	double	atemp;
	int		iter;

	iter = 0;
	while (iter < MAX_ITER)
	{
		a_squared = z_real * z_real;
		b_squared = z_imag * z_imag;
		if (a_squared + b_squared > 4)
			break ;
		atemp = a_squared - b_squared + c_real;
		z_imag = 2 * z_real * z_imag + c_imag;
		z_real = atemp;
		iter++;
	}
	return (iter);
}

void	compute_and_draw_julia(t_fractal *f, int px)
{
	int		py;
	double	z_real;
	double	z_imag;
	int		iter;

	py = 0;
	while (py < HEIGHT)
	{
		z_real = f->min_real + ((double)px / WIDTH) * (f->max_real - f->min_real);
		z_imag = f->min_imag + ((double)py / HEIGHT) * (f->max_imag - f->min_imag);
		iter = julia_pixel_iter(z_real, z_imag, f->julia_real, f->julia_imag);
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
		compute_and_draw_julia(fractal, px);
		px++;
	}
}
