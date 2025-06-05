#include "fractol.h"

int32_t	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 1 || (argc == 2 && (ft_strcmp(argv[1], "mandelbrot") == 0)))
	{
		data.is_julia = 0;
	}
	else if (argc == 4 && (ft_strcmp(argv[1], "julia") == 0))
	{
		data.is_julia = 1;
		data.julia_re = ft_atof(argv[2]);
		data.julia_im = ft_atof(argv[3]);
	}
	else
	{
		ft_printf("Usage:	./fractol mandelbrot\n");
		ft_printf("Or:	./fractol julia <real> <imag>\n");
		return (1); // why is it return(1) and not return(0)?
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
