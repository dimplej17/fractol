#include "fractol.h"

void	ft_error(char *message)
{
	if (message)
		ft_printf("Error: %s\n", message);
	else
		ft_printf("Error\n");
	exit(1);
}

void	print_usage(char *program_name)
{
	ft_printf("Usage: %s <fractal_type> [parameters]\n\n", program_name);
	ft_printf("Available fractal types:\n");
	ft_printf("  mandelbrot                    - Display the Mandelbrot set\n");
	ft_printf("  julia <real> <imag>           - Display Julia set with complex constant c = real + imag*i\n\n");
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
