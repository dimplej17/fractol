/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:21:36 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/12 20:24:17 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	color_band_low(int iter)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = (uint8_t)(9 * iter * 28);
	g = 0;
	b = (uint8_t)(255 - iter * 25);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

uint32_t	color_band_mid(int iter)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	int		band;

	band = iter % 16;
	r = (uint8_t)(255 - band * 15);
	g = (uint8_t)(band * 16);
	b = (uint8_t)(128 + band * 8);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

uint32_t	color_band_high(int iter)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	double	phase;

	phase = (double)iter * 0.1;
	r = (uint8_t)(128 + 127 * sin(phase));
	g = (uint8_t)(128 + 127 * sin(phase + 2.094));
	b = (uint8_t)(128 + 127 * sin(phase + 4.188));
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

uint32_t	get_color(int iter)
{
	if (iter == MAX_ITER)
		return (0x000000FF);
	if (iter < 10)
		return (color_band_low(iter));
	else if (iter < 50)
		return (color_band_mid(iter));
	else
		return (color_band_high(iter));
}
