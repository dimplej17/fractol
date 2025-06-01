# Define program name
NAME = libftprintf.a

# Define source files
SRCS = ft_printf.c \
		ft_putnbr.c \
		ft_putnbr_unsigned.c \
		ft_putstr.c \
		ft_strlen_printf.c \
		ft_hexa_upper.c \
		ft_hexa_lower.c \
		ft_pointer_hexa.c \

# Define object files
OBJS = $(SRCS:%.c=%.o)

# Define compiler
CC = cc

# Define flags for compilation
CFLAGS = -Wall -Wextra -Werror

# Archiver command to create the static library (.a file)
AR = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to remove object files
clean:
		rm -f $(OBJS)

# Rule to remove object files and the program
fclean: clean
		rm -f $(NAME)

# Rule to rebuild the program
re: clean fclean all re

.PHONY: clean fclean all re
