CC = cc
CFLAGS = -Wextra -Werror  -Wall #-fsanitize=address -g #-fsanitize=thread -pthread
RM = rm -rf
SRC = built_in.c minishell.c

OBJ = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ) minishell.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all        
