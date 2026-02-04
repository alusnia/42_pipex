# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Executable Name
NAME = libft.a

GNL_DIR = gnl/

# Source Files (all .c files in the current directory)
LIBFT_FILES = ft_substr.c ft_putnbr_fd.c ft_isdigit.c ft_atoi.c ft_isalpha.c \
        ft_memmove.c ft_isprint.c ft_memchr.c ft_striteri.c ft_putendl_fd.c \
        ft_strmapi.c ft_strrchr.c ft_toupper.c ft_memset.c ft_itoa.c \
        ft_isalnum.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_strjoin.c \
        ft_strlcat.c ft_strdup.c ft_memcmp.c ft_memcpy.c ft_bzero.c ft_tolower.c \
        ft_strchr.c ft_strncmp.c ft_strnstr.c ft_strlcpy.c ft_strlen.c \
        ft_calloc.c ft_isascii.c ft_split.c ft_putptr_fd.c ft_puthex_fd.c ft_putunbr_fd.c \
		ft_putflt_fd.c ft_isspace.c ft_atod.c ft_putdbl_fd.c ft_atol.c \
		ft_printf.c

GNL_FILES = $(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c)

FILES = $(LIBFT_FILES) $(GNL_FILES)

# Object Files
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c libft.h $(GNL_DIR)get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
