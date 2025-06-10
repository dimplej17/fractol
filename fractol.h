#ifndef FRACTOL_H
# define FRACTOL_H
# include "MLX42/include/MLX42/MLX42.h"
# include "ft_printf_42/ft_printf.h"
# include "libft_42/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
#define MIN_REAL -2.0
#define MAX_REAL  2.0
#define MIN_IMAG -1.5
#define MAX_IMAG  1.5
# define MAX_ITER 1000

// Structure to hold fractal parameters and MLX data
typedef struct s_fractal
{
    mlx_t       *mlx;
    mlx_image_t *img;
    double      min_real;
    double      max_real;
    double      min_imag;
    double      max_imag;
    double      zoom_factor;
} t_fractal;
void draw_mandelbrot(t_fractal *fractal);
uint32_t get_color(int iter, double x, double y);







#endif
