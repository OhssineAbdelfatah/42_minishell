CC = cc
CFLAGS = -Wall -Wextra -Werror
BUILTINS := builtins/cd.c \
			# builtins/echo.c \
			# builtins/env.c \
			# builtins/exit.c \
			# builtins/export.c \
			# builtins/pwd.c \
			# builtins/unset.c
SRC = $(BUILTINS) minishell.c 
HEADER := includes/minishell.h
RED = \033[0;31m
GREEN = \033[0;32m
END = \033[0m

LIBFT_DIR = ./includes/libft
LIBFT = ./includes/libft/libft.a

OBJ = $(SRC:.c=.o)
NAME = minishell


all: $(NAME)

$(LIBFT) : 
	@echo "$(GREEN)libft... $(END)"
	@make -C $(LIBFT_DIR)

$(NAME) : $(OBJ) $(LIBFT) $(HEADER)
	@echo "$(GREEN)minishell...$(END)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)clean libft $(END)"
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)clean push_swap $(END)"
	rm -fr $(OBJ)   

fclean: clean
	rm -fr $(NAME) $(LIBFT)

re: fclean all

.PHONY : clean
