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
# define HEIGHT 800
# define MAX_ITER 100

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			is_julia;
	double		julia_re;
	double		julia_im;
}				t_data;

void			draw_mandelbrot(t_data *data);
void			draw_julia(t_data *data);
int				get_color(int iter);
void			put_pixel(mlx_image_t *img, int x, int y, int color);
double			ft_atof(char *str);
int				ft_strcmp(char *s1, char *s2);

#endif