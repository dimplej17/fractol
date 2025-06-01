#include "fractol.h"

int32_t	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1 || (argc == 2 && !strcmp(argv[1], "mandelbrot")))
	{
		data.is_julia = 0;
	}
	else if (argc == 4 && !strcmp(argv[1], "julia"))
	{
		data.is_julia = 1;
		data.julia_re = atof(argv[2]);
		data.julia_im = atof(argv[3]);
	}
	else
	{
		ft_printf("Usage: ./fractol mandelbrot\n");
		ft_printf("   or: ./fractol julia <real> <imag>\n");
		return (1);
	}
	mlx_set_setting(MLX_MAXIMIZED, false);
	data.mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img)
		exit(EXIT_FAILURE);
	if (data.is_julia)
		draw_julia(&data);
	else
		draw_mandelbrot(&data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
