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
#include <stdint.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 300

// Structure to hold fractal parameters and MLX data
typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		min_real;
	double		max_real;
	double		min_imag;
	double		max_imag;
	double 		julia_real;
	double 		julia_imag;
	int 		fractal_type;   // 0 = Mandelbrot, 1 = Julia
	char 		*fractal_name; 
}				t_fractal;
void			compute_and_draw_row(t_fractal *f, int px);
int				mandelbrot_pixel_iter(double a, double b);
void			draw_mandelbrot(t_fractal *fractal);
uint32_t		color_band_high(int iter);
uint32_t		color_band_mid(int iter);
uint32_t		color_band_low(int iter);
uint32_t		get_color(int iter);
int				julia_pixel_iter(double x, double y, double c_real, double c_imag);
void			compute_and_draw_julia_row(t_fractal *f, int px);
void			draw_julia(t_fractal *fractal);
void			draw_fractal(t_fractal *fractal);
int				ft_strcmp(char *s1, char *s2);
int				skip_whitespace_and_sign(char *str, int *sign);
int				parse_integer_part(char *str, int *i);
double			parse_decimal_part(char *str, int *i);
double			ft_atod(char *str);
double			screen_to_real(int px, t_fractal *fractal);
double			screen_to_imag(int py, t_fractal *fractal);
void			zoom_at_point(t_fractal *fractal, int mouse_x, int mouse_y,
					double zoom_factor);
void			scroll_hook(double xdelta, double ydelta, void *param);
void			mouse_hook(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
void			close_hook(void *param);
void			ft_error(char *message);
void			print_usage(char *program_name);
int				setup_mandelbrot(t_fractal *fractal);
int				setup_julia_params(char *arg1, char *arg2, t_fractal *fractal);
int				setup_julia(char *argv[], int argc, t_fractal *fractal);
int				parse_arguments(int argc, char *argv[], t_fractal *fractal);
void			print_controls(void);
int				is_valid_double(char *str, double *out);

#endif
