#include "fractol.h"

uint32_t get_color(int iter)
{
    if (iter == MAX_ITER)
        return 0x000000FF; // Black for points in the set
    
    uint8_t r, g, b;
    
    if (iter < 10)
    {
        // Very close to set - dark colors
        r = (uint8_t)(9 * iter * 28);
        g = 0;
        b = (uint8_t)(255 - iter * 25);
    }
    else if (iter < 50)
    {
        // Medium distance - bright colors
        int band = iter % 16;
        r = (uint8_t)(255 - band * 15);
        g = (uint8_t)(band * 16);
        b = (uint8_t)(128 + band * 8);
    }
    else
    {
        // Far from set - gradient colors
        double phase = (double)iter * 0.1;
        r = (uint8_t)(128 + 127 * sin(phase));
        g = (uint8_t)(128 + 127 * sin(phase + 2.094)); // 2π/3
        b = (uint8_t)(128 + 127 * sin(phase + 4.188)); // 4π/3
    }
    
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}

void draw_mandelbrot(t_fractal *fractal)
{
    for (int px = 0; px < WIDTH; px++)
    {
        for (int py = 0; py < HEIGHT; py++)
        {
            double a = fractal->min_real + ((double)px / (double)WIDTH) * (fractal->max_real - fractal->min_real);
            double b = fractal->min_imag + ((double)py / (double)HEIGHT) * (fractal->max_imag - fractal->min_imag);
            
            double x = 0.0, y = 0.0;
            int iter = 0;

            while (iter < MAX_ITER)
            {
                double x_squared = x * x;
                double y_squared = y * y;
                if (x_squared + y_squared > 4.0)
                    break;
                double xtemp = x_squared - y_squared + a;
                y = 2.0 * x * y + b;
                x = xtemp;
                iter++;
            }
            mlx_put_pixel(fractal->img, px, py, get_color(iter));
        }
    }
}

void draw_julia(t_fractal *fractal)
{
    for (int px = 0; px < WIDTH; px++)
    {
        for (int py = 0; py < HEIGHT; py++)
        {
            // Map pixel to complex plane - this becomes our starting z value
            double x = fractal->min_real + ((double)px / (double)WIDTH) * (fractal->max_real - fractal->min_real);
            double y = fractal->min_imag + ((double)py / (double)HEIGHT) * (fractal->max_imag - fractal->min_imag);
            
            // Julia constant (fixed for all points)
            double c_real = fractal->julia_real;
            double c_imag = fractal->julia_imag;
            
            int iter = 0;
            
            // Julia set iteration with early bailout
            while (iter < MAX_ITER)
            {
                double x_squared = x * x;
                double y_squared = y * y;
                
                // Check for escape condition
                if (x_squared + y_squared > 4.0)
                    break;
                
                // Julia iteration: z = z² + c (where c is constant)
                double xtemp = x_squared - y_squared + c_real;
                y = 2.0 * x * y + c_imag;
                x = xtemp;
                iter++;
            }

            mlx_put_pixel(fractal->img, px, py, get_color(iter));
        }
    }
}

void draw_fractal(t_fractal *fractal)
{
    if (fractal->fractal_type == 0)
        draw_mandelbrot(fractal);
    else
        draw_julia(fractal);
}


