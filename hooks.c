/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:21:11 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/12 20:32:09 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Zoom function - centers zoom on the given screen coordinates
void	zoom_at_point(t_fractal *fractal, int mouse_x, int mouse_y,
		double zoom_factor)
{
	t_zoom	z;

	z.center_real = screen_to_real(mouse_x, fractal);
	z.center_imag = screen_to_imag(mouse_y, fractal);
	z.real_range = fractal->max_real - fractal->min_real;
	z.imag_range = fractal->max_imag - fractal->min_imag;
	z.new_real_range = z.real_range * zoom_factor;
	z.new_imag_range = z.imag_range * zoom_factor;
	fractal->min_real = z.center_real - z.new_real_range / 2.0;
	fractal->max_real = z.center_real + z.new_real_range / 2.0;
	fractal->min_imag = z.center_imag - z.new_imag_range / 2.0;
	fractal->max_imag = z.center_imag + z.new_imag_range / 2.0;
}

// Mouse scroll hook for zooming
void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;
	int32_t		mouse_x;
	int32_t		mouse_y;

	(void)xdelta;
	fractal = (t_fractal *)param;
	mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
	if (mouse_x >= 0 && mouse_x < WIDTH && mouse_y >= 0 && mouse_y < HEIGHT)
	{
		if (ydelta > 0)
		{
			zoom_at_point(fractal, mouse_x, mouse_y, 0.8);
		}
		else if (ydelta < 0)
		{
			zoom_at_point(fractal, mouse_x, mouse_y, 1.25);
		}
		draw_fractal(fractal);
	}
}

// Mouse click hook for zooming
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_fractal	*fractal;
	int32_t		mouse_x;
	int32_t		mouse_y;

	(void)mods;
	fractal = (t_fractal *)param;
	if (action == MLX_PRESS)
	{
		mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
		if (mouse_x >= 0 && mouse_x < WIDTH && mouse_y >= 0 && mouse_y < HEIGHT)
		{
			if (button == MLX_MOUSE_BUTTON_LEFT)
			{
				zoom_at_point(fractal, mouse_x, mouse_y, 0.5);
			}
			else if (button == MLX_MOUSE_BUTTON_RIGHT)
			{
				zoom_at_point(fractal, mouse_x, mouse_y, 2.0);
			}
			draw_fractal(fractal);
		}
	}
}

// Key hook for controls
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(fractal->mlx);
	}
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		if (fractal->fractal_type == 0)
		{
			fractal->min_real = -2.2;
			fractal->max_real = 0.8;
			fractal->min_imag = -1.5;
			fractal->max_imag = 1.5;
		}
		else
		{
			fractal->min_real = -2.0;
			fractal->max_real = 2.0;
			fractal->min_imag = -2.0;
			fractal->max_imag = 2.0;
		}
		draw_fractal(fractal);
	}
}

// Close hook to handle window close button
void	close_hook(void *param)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)param;
	mlx_close_window(fractal->mlx);
}
