/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:21:44 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/12 20:24:12 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Convert screen coordinates to complex plane coordinates
double	screen_to_real(int px, t_fractal *fractal)
{
	return (fractal->min_real + ((double)px / WIDTH) * (fractal->max_real
			- fractal->min_real));
}

double	screen_to_imag(int py, t_fractal *fractal)
{
	return (fractal->min_imag + ((double)py / HEIGHT) * (fractal->max_imag
			- fractal->min_imag));
}
