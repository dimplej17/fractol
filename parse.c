#include "fractol.h"

int	is_valid_double(char *str, double *out)
{
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

	if (!is_valid_double(arg1, &real) || !is_valid_double(arg2, &imag))
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
	static char	title[256];

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
	snprintf(title, sizeof(title), "Julia Set: c = %.4f + %.4fi",
		fractal->julia_real, fractal->julia_imag);
	fractal->fractal_name = title;
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
