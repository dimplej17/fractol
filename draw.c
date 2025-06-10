#include "fractol.h"

uint32_t get_color(int iter, double x, double y)
{
	if (iter == MAX_ITER)
		return 0x000000FF;

	// Smooth coloring using log
	double mag = sqrt(x * x + y * y);
	double smooth = iter + 1 - log(log(mag)) / log(2.0);

	// Psychedelic coloring using sine waves
	uint8_t r = (uint8_t)(sin(0.016 * smooth + 0) * 127 + 128);
	uint8_t g = (uint8_t)(sin(0.016 * smooth + 2) * 127 + 128);
	uint8_t b = (uint8_t)(sin(0.016 * smooth + 4) * 127 + 128);

	return (r << 24 | g << 16 | b << 8 | 0xFF);  // ARGB
}

// (px, py) → mapped to C = a + bi
// Z = 0 → loop → Z = Z² + C
// If Z "escapes" (|Z| > 2), we stop.
// Color pixel based on how quickly it escaped.
// void draw_mandelbrot(mlx_image_t *img)
// {
// 	for (int px = 0; px < WIDTH; px++)
// 	{
// 		for (int py = 0; py < HEIGHT; py++)
// 		{
// 			double a = MIN_REAL + ((double)px / WIDTH) * (MAX_REAL - MIN_REAL);
// 			double b = MIN_IMAG + ((double)py / HEIGHT) * (MAX_IMAG - MIN_IMAG);
// 			double x = 0, y = 0;
// 			int iter = 0;

// 			while (x * x + y * y <= 4.0 && iter < MAX_ITER)
// 			{
// 				double xtemp = x * x - y * y + a;
// 				y = 2 * x * y + b;
// 				x = xtemp;
// 				iter++;
// 			}

// 			mlx_put_pixel(img, px, py, get_color(iter, x, y));
// 		}
// 	}
// }

void draw_mandelbrot(t_fractal *fractal)
{
    for (int px = 0; px < WIDTH; px++)
    {
        for (int py = 0; py < HEIGHT; py++)
        {
            double a = fractal->min_real + ((double)px / WIDTH) * (fractal->max_real - fractal->min_real);
            double b = fractal->min_imag + ((double)py / HEIGHT) * (fractal->max_imag - fractal->min_imag);
            double x = 0, y = 0;
            int iter = 0;

            while (x * x + y * y <= 4.0 && iter < MAX_ITER)
            {
                double xtemp = x * x - y * y + a;
                y = 2 * x * y + b;
                x = xtemp;
                iter++;
            }

            mlx_put_pixel(fractal->img, px, py, get_color(iter, x, y));
        }
    }
}
