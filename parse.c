/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:21:21 by djanardh          #+#    #+#             */
/*   Updated: 2025/06/12 20:23:48 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_valid_double(char *str, double *out, int i)
{
	int has_dot = 0;
	int has_digit = 0;

	if (!str || !*str)
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (-1);
			has_dot = 1;
		}
		else if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else
			return (-1);
		i++;
	}
	if (!has_digit)
		return (-1);
	*out = ft_atod(str);
	return (1);
}

int	setup_mandelbrot(t_fractal *fractal)
{
	fractal->fractal_type = 0;
	fractal->fractal_name = "Mandelbrot Set";
	fractal->min_real = -2.2;
	fractal->max_real = 0.8;
	fractal->min_imag = -1.5;
	fractal->max_imag = 1.5;
	return (1);
}

int	setup_julia_params(char *arg1, char *arg2, t_fractal *fractal)
{
	double	real;
	double	imag;

	if (is_valid_double(arg1, &real, 0) < 0 || is_valid_double(arg2, &imag, 0) < 0)
	{
		ft_printf("Error: Invalid Julia constants\n\n");
		return (0);
	}
	fractal->julia_real = real;
	fractal->julia_imag = imag;
	return (1);
}

int	setup_julia(char *argv[], int argc, t_fractal *fractal)
{
	if (argc != 4)
	{
		ft_printf("Error: Julia set requires exactly 2 parameters\n\n");
		return (0);
	}
	if (!setup_julia_params(argv[2], argv[3], fractal))
		return (0);
	fractal->fractal_type = 1;
	fractal->min_real = -2.0;
	fractal->max_real = 2.0;
	fractal->min_imag = -2.0;
	fractal->max_imag = 2.0;
	fractal->fractal_name = "Julia Set";
	return (1);
}

int	parse_arguments(int argc, char *argv[], t_fractal *fractal)
{
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (0);
	}
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		return (setup_mandelbrot(fractal));
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (!setup_julia(argv, argc, fractal))
		{
			print_usage(argv[0]);
			return (0);
		}
		return (1);
	}
	ft_printf("Error: Unknown fractal type '%s'\n\n", argv[1]);
	print_usage(argv[0]);
	return (0);
}
