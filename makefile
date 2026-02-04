# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Executable Name
NAME = pipex

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

FILES = main.c pipex_utils.c init_data.c

# Object Files
OBJS = $(FILES:.c=.o)

# Headers
HEADERS = pipex.h $(LIBFT_DIR)/libft.h

# Default target
all: $(NAME)

# Build executable
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Remove executables and object files
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
