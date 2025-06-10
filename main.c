#include "fractol.h"

double screen_to_real(int px, t_fractal *fractal)
{
    return fractal->min_real + ((double)px / WIDTH) * (fractal->max_real - fractal->min_real);
}

double screen_to_imag(int py, t_fractal *fractal)
{
    return fractal->min_imag + ((double)py / HEIGHT) * (fractal->max_imag - fractal->min_imag);
}

// Zoom function - centers zoom on the given screen coordinates
void zoom_at_point(t_fractal *fractal, int mouse_x, int mouse_y, double zoom_factor)
{
    // Convert mouse position to complex coordinates
    double center_real = screen_to_real(mouse_x, fractal);
    double center_imag = screen_to_imag(mouse_y, fractal);
    
    // Calculate current ranges
    double real_range = fractal->max_real - fractal->min_real;
    double imag_range = fractal->max_imag - fractal->min_imag;
    
    // Apply zoom (smaller zoom_factor = zoom in, larger = zoom out)
    double new_real_range = real_range * zoom_factor;
    double new_imag_range = imag_range * zoom_factor;
    
    // Center the new range on the mouse cursor
    fractal->min_real = center_real - new_real_range / 2.0;
    fractal->max_real = center_real + new_real_range / 2.0;
    fractal->min_imag = center_imag - new_imag_range / 2.0;
    fractal->max_imag = center_imag + new_imag_range / 2.0;
}

// Mouse scroll hook for zooming
void scroll_hook(double xdelta, double ydelta, void *param)
{
    (void)xdelta;
    t_fractal *fractal = (t_fractal *)param;
    int32_t mouse_x, mouse_y;
    
    // Get current mouse position
    mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
    
    // Check if mouse is within window bounds
    if (mouse_x >= 0 && mouse_x < WIDTH && mouse_y >= 0 && mouse_y < HEIGHT)
    {
        if (ydelta > 0) // Scroll up - zoom in
        {
            zoom_at_point(fractal, mouse_x, mouse_y, 0.8);
        }
        else if (ydelta < 0) // Scroll down - zoom out
        {
            zoom_at_point(fractal, mouse_x, mouse_y, 1.25);
        }
        
        // Redraw the fractal
        draw_mandelbrot(fractal);
    }
}

// Mouse click hook for zooming (optional - alternative to scroll)
void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
    (void)mods;
    t_fractal *fractal = (t_fractal *)param;
    int32_t mouse_x, mouse_y;
    
    if (action == MLX_PRESS)
    {
        mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
        
        if (mouse_x >= 0 && mouse_x < WIDTH && mouse_y >= 0 && mouse_y < HEIGHT)
        {
            if (button == MLX_MOUSE_BUTTON_LEFT) // Left click - zoom in
            {
                zoom_at_point(fractal, mouse_x, mouse_y, 0.5);
            }
            else if (button == MLX_MOUSE_BUTTON_RIGHT) // Right click - zoom out
            {
                zoom_at_point(fractal, mouse_x, mouse_y, 2.0);
            }
            
            // Redraw the fractal
            draw_mandelbrot(fractal);
        }
    }
}

// Key hook for reset and other controls
void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fractal *fractal = (t_fractal *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(fractal->mlx);
    }
    else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS) // Reset zoom
    {
        fractal->min_real = -2.5;
        fractal->max_real = 1.0;
        fractal->min_imag = -1.25;
        fractal->max_imag = 1.25;
        draw_mandelbrot(fractal);
    }
}

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// int main()
// {
//     mlx_t *mlx;
//     mlx_image_t *img;

//     mlx = mlx_init(WIDTH, HEIGHT, "Fractal", true);
//     if (!mlx)
//         ft_error();  // Handle error

//     // Create a new image and check if it was created successfully
//     img = mlx_new_image(mlx, WIDTH, HEIGHT);
//     if (!img)
//         ft_error();  // Handle error

//     // Do stuff
//     draw_mandelbrot(img);


//     // Display the image in the window at position (0, 0)
//     mlx_image_to_window(mlx, img, 0, 0);

//     mlx_scroll_hook(mlx, scroll_hook, &vars);
//     // Keep the window open until the user closes it
//     mlx_loop(mlx);

//     return 0;
// }

int main()
{
    t_fractal fractal;
    
    // Initialize fractal parameters
    fractal.min_real = -2.5;
    fractal.max_real = 1.0;
    fractal.min_imag = -1.25;
    fractal.max_imag = 1.25;
    fractal.zoom_factor = 1.0;
    
    // Initialize MLX
    fractal.mlx = mlx_init(WIDTH, HEIGHT, "Mandelbrot Fractal - Zoom with Mouse", true);
    if (!fractal.mlx)
        ft_error();
    
    // Create image
    fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
    if (!fractal.img)
        ft_error();
    
    // Draw initial fractal
    draw_mandelbrot(&fractal);
    
    // Display image
    mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
    
    // Set up hooks
    mlx_scroll_hook(fractal.mlx, scroll_hook, &fractal);
    mlx_mouse_hook(fractal.mlx, mouse_hook, &fractal);
    mlx_key_hook(fractal.mlx, key_hook, &fractal);
    
    // Start the main loop
    mlx_loop(fractal.mlx);
    
    // Cleanup
    mlx_delete_image(fractal.mlx, fractal.img);
    mlx_terminate(fractal.mlx);
    
    return 0;
}