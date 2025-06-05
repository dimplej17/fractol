#include "fractol.h"

void draw_mandelbrot(t_data *data)
{
    int x, y, i;
    double zx, zy, cx, cy, tmp;
    double scale = 4.0 / (WIDTH * data->zoom);  // Correct scaling based on zoom

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            zx = zy = 0;
            cx = (x - WIDTH / 2) * scale + data->offset_x;  // Use offset_x for smooth panning
            cy = (y - HEIGHT / 2) * scale + data->offset_y; // Use offset_y for smooth panning
            i = 0;
            while (zx * zx + zy * zy < 4 && i < data->max_iter)
            {
                tmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = tmp;
                i++;
            }

            if (i == data->max_iter)
{
    uint32_t color = 0x000000FF; // Black for points in the set
    mlx_put_pixel(data->img, x, y, color);
}
else
{
    double t = (double)i / data->max_iter;
    
    // Rainbow HSV color calculation
    double hue = fmod(t * 360.0 * 3, 360.0); // 3 full rainbow cycles
    double saturation = 1.0;
    double value = 1.0;
    
    // Convert HSV to RGB
    double c = value * saturation;
    double x_val = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    double m = value - c;
    
    double r, g, b;
    if (hue < 60) { r = c; g = x_val; b = 0; }
    else if (hue < 120) { r = x_val; g = c; b = 0; }
    else if (hue < 180) { r = 0; g = c; b = x_val; }
    else if (hue < 240) { r = 0; g = x_val; b = c; }
    else if (hue < 300) { r = x_val; g = 0; b = c; }
    else { r = c; g = 0; b = x_val; }
    
    uint8_t red = (uint8_t)((r + m) * 255);
    uint8_t green = (uint8_t)((g + m) * 255);
    uint8_t blue = (uint8_t)((b + m) * 255);
    
    uint32_t color = (red << 24) | (green << 16) | (blue << 8) | 255;
    mlx_put_pixel(data->img, x, y, color);
}
        }
    }
}

void draw_julia(t_data *data)
{
    int x, y, i;
    double zx, zy, tmp;
    double scale = 4.0 / (WIDTH * data->zoom);  // Correct scaling based on zoom
    double cx = data->julia_re;
    double cy = data->julia_im;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            zx = (x - WIDTH / 2) * scale + data->offset_x;  // Use offset_x for smooth panning
            zy = (y - HEIGHT / 2) * scale + data->offset_y; // Use offset_y for smooth panning
            i = 0;
            while (zx * zx + zy * zy < 4 && i < data->max_iter)
            {
                tmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = tmp;
                i++;
            }

            if (i == data->max_iter)
{
    uint32_t color = 0x000000FF; // Black for points in the set
    mlx_put_pixel(data->img, x, y, color);
}
else
{
    double t = (double)i / data->max_iter;
    
    // Rainbow HSV color calculation
    double hue = fmod(t * 360.0 * 3, 360.0); // 3 full rainbow cycles
    double saturation = 1.0;
    double value = 1.0;
    
    // Convert HSV to RGB
    double c = value * saturation;
    double x_val = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    double m = value - c;
    
    double r, g, b;
    if (hue < 60) { r = c; g = x_val; b = 0; }
    else if (hue < 120) { r = x_val; g = c; b = 0; }
    else if (hue < 180) { r = 0; g = c; b = x_val; }
    else if (hue < 240) { r = 0; g = x_val; b = c; }
    else if (hue < 300) { r = x_val; g = 0; b = c; }
    else { r = c; g = 0; b = x_val; }
    
    uint8_t red = (uint8_t)((r + m) * 255);
    uint8_t green = (uint8_t)((g + m) * 255);
    uint8_t blue = (uint8_t)((b + m) * 255);
    
    uint32_t color = (red << 24) | (green << 16) | (blue << 8) | 255;
    mlx_put_pixel(data->img, x, y, color);
}
        }
    }
}
