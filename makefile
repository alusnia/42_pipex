# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Executable Name
NAME = pipex

# Source Files (all .c files in the current directory)
LIBFT_FILES = $(addprefix libft/, ft_substr.c ft_putnbr_fd.c ft_isdigit.c ft_atoi.c ft_isalpha.c \
        ft_memmove.c ft_isprint.c ft_memchr.c ft_striteri.c ft_putendl_fd.c \
        ft_strmapi.c ft_strrchr.c ft_toupper.c ft_memset.c ft_itoa.c \
        ft_isalnum.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_strjoin.c \
        ft_strlcat.c ft_strdup.c ft_memcmp.c ft_memcpy.c ft_bzero.c ft_tolower.c \
        ft_strchr.c ft_strncmp.c ft_strnstr.c ft_strlcpy.c ft_strlen.c \
        ft_calloc.c ft_isascii.c ft_split.c ft_lstsize.c ft_lstnew.c ft_lstlast.c \
        ft_lstdelone.c ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstiter.c ft_lstmap.c ft_putptr_fd.c ft_puthex_fd.c ft_putunbr_fd.c \
		ft_putflt_fd.c ft_printf.c ft_isspace.c ft_atod.c ft_putdbl_fd.c ft_atol.c)

GNL_FILES = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)

PIPEX_FILES = main.c pipex_utils.c init_data.c

FILES = $(PIPEX_FILES) $(LIBFT_FILES) $(GNL_FILES)

# Object Files
OBJS = $(FILES:.c=.o)

# Headers
HEADERS = pipex.h libft/libft.h gnl/get_next_line.h

# Default target
all: $(NAME)

# Build executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Remove executables and object files
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
