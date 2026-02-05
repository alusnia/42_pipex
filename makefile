CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g -I$(LIB_DIR)/incs -I$(INCS_DIR)

NAME		= pipex

LIB_DIR		= ./lib

LIB			= $(LIB_DIR)/libftplus.a

INCS_DIR	= ./incs

INCS 		= $(INCS_DIR)/pipex.h

OBJS_DIR	= ./objs

OBJS		= $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

SRCS_DIR	= ./srcs

SRCS		= main.c pipex_utils.c init_data.c

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

del_lib:
	@echo $(SEP)
	@echo "Deleting library libftplus..."
	@echo $(SEP)
	$(MAKE) -C $(LIB_DIR) del_lib

.PHONY: all clean fclean re del_lib
