#include "fractol.h"

// Convert screen coordinates to complex plane coordinates
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
        draw_fractal(fractal);
    }
}

// Mouse click hook for zooming
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
            draw_fractal(fractal);
        }
    }
}

// Key hook for controls
void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fractal *fractal = (t_fractal *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        // Clean exit
        mlx_close_window(fractal->mlx);
    }
    else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS) // Reset zoom
    {
        if (fractal->fractal_type == 0) // Mandelbrot
        {
            fractal->min_real = -2.2;
            fractal->max_real = 0.8;
            fractal->min_imag = -1.5;
            fractal->max_imag = 1.5;
        }
        else // Julia
        {
            fractal->min_real = -2.0;
            fractal->max_real = 2.0;
            fractal->min_imag = -2.0;
            fractal->max_imag = 2.0;
        }
        draw_fractal(fractal);
    }
}

// Optional: Close hook to handle window close button
void close_hook(void *param)
{
    t_fractal *fractal = (t_fractal *)param;
    mlx_close_window(fractal->mlx);
}

void ft_error(char *message)
{
    if (message)
        fprintf(stderr, "Error: %s\n", message);
    else
        fprintf(stderr, "Error\n");
    exit(1);
}

void print_usage(char *program_name)
{
    printf("Usage: %s <fractal_type> [parameters]\n\n", program_name);
    printf("Available fractal types:\n");
    printf("  mandelbrot                    - Display the Mandelbrot set\n");
    printf("  julia <real> <imag>          - Display Julia set with complex constant c = real + imag*i\n\n");
    printf("Examples:\n");
    printf("  %s mandelbrot\n", program_name);
    printf("  %s julia -0.7269 0.1889      # Classic Julia set\n", program_name);
    printf("  %s julia -0.4 0.6            # Lightning pattern\n", program_name);
    printf("  %s julia 0.285 0.01          # Spiral pattern\n", program_name);
    printf("  %s julia -0.8 0.156          # Feather pattern\n", program_name);
    printf("  %s julia -0.123 0.745        # Dragon pattern\n", program_name);
    printf("\nControls:\n");
    printf("  Mouse Scroll: Zoom in/out at cursor\n");
    printf("  Left Click: Zoom in\n");
    printf("  Right Click: Zoom out\n");
    printf("  R: Reset view\n");
    printf("  ESC: Exit\n");
}

int parse_arguments(int argc, char **argv, t_fractal *fractal)
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 0;
    }
    
    // Check fractal type
    if (strcmp(argv[1], "mandelbrot") == 0)
    {
        fractal->fractal_type = 0;
        fractal->fractal_name = "Mandelbrot Set";
        
        // Set default Mandelbrot view
        fractal->min_real = -2.2;
        fractal->max_real = 0.8;
        fractal->min_imag = -1.5;
        fractal->max_imag = 1.5;
        
        printf("Displaying Mandelbrot set\n");
        return 1;
    }
    else if (strcmp(argv[1], "julia") == 0)
    {
        if (argc != 4)
        {
            printf("Error: Julia set requires exactly 2 parameters (real and imaginary parts)\n\n");
            print_usage(argv[0]);
            return 0;
        }
        
        // Parse Julia constants
        char *endptr;
        fractal->julia_real = strtod(argv[2], &endptr);
        if (*endptr != '\0')
        {
            printf("Error: Invalid real part '%s'\n\n", argv[2]);
            print_usage(argv[0]);
            return 0;
        }
        
        fractal->julia_imag = strtod(argv[3], &endptr);
        if (*endptr != '\0')
        {
            printf("Error: Invalid imaginary part '%s'\n\n", argv[3]);
            print_usage(argv[0]);
            return 0;
        }
        
        fractal->fractal_type = 1;
        
        // Create dynamic window title
        static char title[256];
        snprintf(title, sizeof(title), "Julia Set: c = %.4f + %.4fi", 
                fractal->julia_real, fractal->julia_imag);
        fractal->fractal_name = title;
        
        // Set default Julia view
        fractal->min_real = -2.0;
        fractal->max_real = 2.0;
        fractal->min_imag = -2.0;
        fractal->max_imag = 2.0;
        
        printf("Displaying Julia set with c = %.4f + %.4fi\n", 
               fractal->julia_real, fractal->julia_imag);
        return 1;
    }
    else
    {
        printf("Error: Unknown fractal type '%s'\n\n", argv[1]);
        print_usage(argv[0]);
        return 0;
    }
}

void print_controls(void)
{
    printf("\n=== FRACTAL CONTROLS ===\n");
    printf("Mouse Scroll: Zoom in/out at cursor\n");
    printf("Left Click: Zoom in\n");
    printf("Right Click: Zoom out\n");
    printf("R: Reset view\n");
    printf("ESC: Exit\n");
    printf("========================\n\n");
}

int main(int argc, char **argv)
{
    t_fractal fractal;
    
    // Parse command line arguments
    if (!parse_arguments(argc, argv, &fractal))
        return 1;
    
    // Print controls
    print_controls();
    
    // Initialize MLX with dynamic title
    fractal.mlx = mlx_init(WIDTH, HEIGHT, fractal.fractal_name, true);
    if (!fractal.mlx)
        ft_error("Failed to initialize MLX");
    
    // Create image
    fractal.img = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
    if (!fractal.img)
        ft_error("Failed to create image");
    
    // Draw initial fractal
    printf("Rendering fractal...\n");
    draw_fractal(&fractal);
    printf("Fractal rendered successfully!\n");
    
    // Display image
    mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);
    
    // Set up hooks
    mlx_scroll_hook(fractal.mlx, scroll_hook, &fractal);
    mlx_mouse_hook(fractal.mlx, mouse_hook, &fractal);
    mlx_key_hook(fractal.mlx, key_hook, &fractal);
    mlx_close_hook(fractal.mlx, close_hook, &fractal);
    
    // Start the main loop
    mlx_loop(fractal.mlx);
    
    // Cleanup
    mlx_delete_image(fractal.mlx, fractal.img);
    mlx_terminate(fractal.mlx);
    
    return 0;
}