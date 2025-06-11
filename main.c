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

// Zoom function - centers zoom on the given screen coordinates
void	zoom_at_point(t_fractal *fractal, int mouse_x, int mouse_y,
		double zoom_factor)
{
	double	center_real;
	double	center_imag;
	double	real_range;
	double	imag_range;
	double	new_real_range;
	double	new_imag_range;

	center_real = screen_to_real(mouse_x, fractal);
	center_imag = screen_to_imag(mouse_y, fractal);
	real_range = fractal->max_real - fractal->min_real;
	imag_range = fractal->max_imag - fractal->min_imag;
	new_real_range = real_range * zoom_factor;
	new_imag_range = imag_range * zoom_factor;
	fractal->min_real = center_real - new_real_range / 2.0;
	fractal->max_real = center_real + new_real_range / 2.0;
	fractal->min_imag = center_imag - new_imag_range / 2.0;
	fractal->max_imag = center_imag + new_imag_range / 2.0;
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

void	ft_error(char *message)
{
	if (message)
		fprintf(stderr, "Error: %s\n", message);
	else
		fprintf(stderr, "Error\n");
	exit(1);
}

void	print_usage(char *program_name)
{
	ft_printf("Usage: %s <fractal_type> [parameters]\n\n", program_name);
	ft_printf("Available fractal types:\n");
	ft_printf("  mandelbrot                    - Display the Mandelbrot set\n");
	ft_printf("  julia <real> <imag>         
		- Display Julia set with complex constant c = real + imag*i\n\n");
	ft_printf("Examples:\n");
	ft_printf("  %s mandelbrot\n", program_name);
	ft_printf("  %s julia -0.7269 0.1889      # Classic Julia set\n",
		program_name);
	ft_printf("  %s julia -0.4 0.6            # Lightning pattern\n",
		program_name);
	ft_printf("  %s julia 0.285 0.01          # Spiral pattern\n",
		program_name);
	ft_printf("  %s julia -0.8 0.156          # Feather pattern\n",
		program_name);
	ft_printf("  %s julia -0.123 0.745        # Dragon pattern\n",
		program_name);
}

// In parse.c or similar file
// not included in header
static int	is_valid_double(const char *str, double *out)
{
	char	*endptr;

	*out = strtod(str, &endptr);
	return (*endptr == '\0');
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
	if (strcmp(argv[1], "mandelbrot") == 0)
		return (setup_mandelbrot(fractal));
	else if (strcmp(argv[1], "julia") == 0)
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

void	print_controls(void)
{
	ft_printf("\n=== FRACTAL CONTROLS ===\n");
	ft_printf("Mouse Scroll: Zoom in/out at cursor\n");
	ft_printf("Left Click: Zoom in\n");
	ft_printf("Right Click: Zoom out\n");
	ft_printf("R: Reset view\n");
	ft_printf("ESC: Exit\n");
	ft_printf("========================\n\n");
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (!parse_arguments(argc, argv, &fractal))
		return (1);
	print_controls();
	fractal.mlx = mlx_init(WIDTH, HEIGHT, fractal.fractal_name, true);
	if (!fractal.mlx)
		ft_error("Failed to initialize MLX");
	fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	if (!fractal.img)
		ft_error("Failed to create image");
	draw_fractal(&fractal);
	mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
	mlx_scroll_hook(fractal.mlx, scroll_hook, &fractal);
	mlx_mouse_hook(fractal.mlx, mouse_hook, &fractal);
	mlx_key_hook(fractal.mlx, key_hook, &fractal);
	mlx_close_hook(fractal.mlx, close_hook, &fractal);
	mlx_loop(fractal.mlx);
	mlx_delete_image(fractal.mlx, fractal.img);
	mlx_terminate(fractal.mlx);
	return (0);
}
