#include "fractol.h"

void render_fractal(t_data *data)
{
    mlx_delete_image(data->mlx, data->img);
    
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (!data->img)
        exit(EXIT_FAILURE);
    
    if (data->is_julia)
        draw_julia(data);
    else
        draw_mandelbrot(data);
    mlx_image_to_window(data->mlx, data->img, 0, 0);
}

// Mouse cursor position hook to track mouse movement
void cursor_hook(double xpos, double ypos, void *param)
{
    t_data *data = (t_data *)param;
    data->mouse_x = xpos;
    data->mouse_y = ypos;
}

// Scroll hook for zooming at mouse position
void scroll_hook(double xdelta, double ydelta, void *param)
{
    (void)xdelta;
    t_data *data = (t_data *)param;
    
    if (ydelta == 0) return; // No scroll
    
    double zoom_factor = 1.2; // Slightly more aggressive zoom
    
    // Get current scale
    double scale_before = 4.0 / (WIDTH * data->zoom);
    
    // Convert mouse position to complex plane coordinates before zoom
    double complex_x = (data->mouse_x - WIDTH / 2.0) * scale_before + data->offset_x;
    double complex_y = (data->mouse_y - HEIGHT / 2.0) * scale_before + data->offset_y;
    
    // Apply zoom
    if (ydelta > 0)
        data->zoom *= zoom_factor;  // Zoom in
    else
        data->zoom /= zoom_factor;  // Zoom out
    
    // Limit zoom to prevent overflow/underflow
    if (data->zoom > 1e15) data->zoom = 1e15;
    if (data->zoom < 1e-10) data->zoom = 1e-10;
    
    // Get new scale after zoom
    double scale_after = 4.0 / (WIDTH * data->zoom);
    
    // Adjust offset so the complex point under mouse stays under mouse
    data->offset_x = complex_x - (data->mouse_x - WIDTH / 2.0) * scale_after;
    data->offset_y = complex_y - (data->mouse_y - HEIGHT / 2.0) * scale_after;
    
    render_fractal(data);
}

// Mouse button hook for panning (drag to move around)
void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
    (void)mods;
    t_data *data = (t_data *)param;
    
    if (button == MLX_MOUSE_BUTTON_LEFT)
    {
        if (action == MLX_PRESS)
        {
            data->is_dragging = 1;
            data->drag_start_x = data->mouse_x;
            data->drag_start_y = data->mouse_y;
            data->drag_offset_x = data->offset_x;
            data->drag_offset_y = data->offset_y;
        }
        else if (action == MLX_RELEASE)
        {
            data->is_dragging = 0;
        }
    }
}

// Cursor hook for dragging/panning
void cursor_hook_with_drag(double xpos, double ypos, void *param)
{
    t_data *data = (t_data *)param;
    data->mouse_x = xpos;
    data->mouse_y = ypos;
    
    // Handle dragging for panning
    if (data->is_dragging)
    {
        double scale = 4.0 / (WIDTH * data->zoom);
        double dx = (xpos - data->drag_start_x) * scale;
        double dy = (ypos - data->drag_start_y) * scale;
        
        data->offset_x = data->drag_offset_x - dx;
        data->offset_y = data->drag_offset_y - dy;
        
        render_fractal(data);
    }
}

// Key hook for additional controls
void key_hook(mlx_key_data_t keydata, void *param)
{
    t_data *data = (t_data *)param;
    
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        // Reset view
        if (keydata.key == MLX_KEY_R)
        {
            data->zoom = 1.0;
            data->offset_x = 0.0;
            data->offset_y = 0.0;
            render_fractal(data);
        }
        // Increase iterations for more detail when zoomed in
        else if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_KP_ADD)
        {
            data->max_iter += 10;
            if (data->max_iter > 1000) data->max_iter = 1000;
            render_fractal(data);
        }
        // Decrease iterations
        else if (keydata.key == MLX_KEY_MINUS || keydata.key == MLX_KEY_KP_SUBTRACT)
        {
            data->max_iter -= 10;
            if (data->max_iter < 10) data->max_iter = 10;
            render_fractal(data);
        }
        // Quit
        else if (keydata.key == MLX_KEY_ESCAPE)
        {
            mlx_close_window(data->mlx);
        }
    }
}

int32_t main(int argc, char *argv[])
{
    t_data data;
    
    // Initialize all values
    data.offset_x = 0.0;
    data.offset_y = 0.0;
    data.mouse_x = WIDTH / 2.0;
    data.mouse_y = HEIGHT / 2.0;
    data.is_dragging = 0;
    data.drag_start_x = 0.0;
    data.drag_start_y = 0.0;
    data.drag_offset_x = 0.0;
    data.drag_offset_y = 0.0;

    if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0))
        data.is_julia = 0;
    else if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
    {
        data.is_julia = 1;
        data.julia_re = ft_atof(argv[2]);
        data.julia_im = ft_atof(argv[3]);
    }
    else
    {
        ft_printf("Usage: ./fractol mandelbrot\n");
        ft_printf("Or:    ./fractol julia <real> <imag>\n");
        ft_printf("Controls:\n");
        ft_printf("  Mouse wheel: Zoom in/out at cursor\n");
        ft_printf("  Left click + drag: Pan around\n");
        ft_printf("  R: Reset view\n");
        ft_printf("  +/-: Increase/decrease iterations\n");
        ft_printf("  ESC: Quit\n");
        return (1);
    }

    mlx_set_setting(MLX_MAXIMIZED, false);
    data.mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
    if (!data.mlx)
        exit(EXIT_FAILURE);
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    if (!data.img)
        exit(EXIT_FAILURE);

    // Default settings
    data.zoom = 1.0;
    data.max_iter = 50;

    // Initial render
    if (data.is_julia)
        draw_julia(&data);
    else
        draw_mandelbrot(&data);
    
    mlx_image_to_window(data.mlx, data.img, 0, 0);

    // Set up all the hooks
    mlx_scroll_hook(data.mlx, scroll_hook, &data);
    mlx_cursor_hook(data.mlx, cursor_hook_with_drag, &data);
    mlx_mouse_hook(data.mlx, mouse_hook, &data);
    mlx_key_hook(data.mlx, key_hook, &data);

    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return (EXIT_SUCCESS);
}
