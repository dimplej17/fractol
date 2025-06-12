# Define program name
NAME = fractol

# Including libft & ft_printf & ensuring #include "libft.h" works in fractol
LIBFT_DIR = libft_42
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = ft_printf_42
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# MLX 42
MLX_DIR = MLX42
LIBMLX = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Define additional linking flags for macOS frameworks
LINK_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

# Headers
HEADERS = -I . -I $(MLX_DIR)/include -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR)

# Define source files
SRCS =	main.c \
		draw_mandel.c \
		draw_julia.c \
		utils.c \
		parse.c \
		hooks.c \
		coordinates.c \
		color.c

# Define object files
OBJS = $(SRCS:%.c=%.o)

# Define compiler
CC = cc

# Define flags for compilation
CFLAGS = -Wall -Werror -Wextra -Wunreachable-code -Ofast

all: libmlx libft ft_printf $(NAME)

# Clone MLX42 if not already present
$(MLX_DIR):
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

libmlx: $(MLX_DIR)
	@cmake -B $(MLX_DIR)/build $(MLX_DIR)
	@cmake --build $(MLX_DIR)/build -j4

libft:
	@make -C $(LIBFT_DIR)

ft_printf:
	@make -C $(FT_PRINTF_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBMLX) $(LIBFT) $(FT_PRINTF) $(HEADERS) $(LINK_FLAGS) -o $(NAME)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: clean fclean all re libmlx libft ft_printf

