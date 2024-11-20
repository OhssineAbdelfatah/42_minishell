GNL = lib/gnl0/get_next_line.c lib/gnl0/get_next_line_utils.c

PARSE = sources/parse/parse_tools.c sources/parse/parse.c sources/parse/counting_tools.c\
		sources/parse/sub_check.c sources/parse/counting_things.c sources/parse/tokens_part2.c sources/parse/tokens.c\
		sources/parse/new_tools.c
		
REDIRECTION = sources/redirection_things/del.c sources/redirection_things/ordering.c\
				sources/parse/checking_in.c\
				sources/redirection_things/redirection_tools.c sources/redirection_things/herdoc.c

ERRORS  = sources/errors/error.c 

WILDCARD_FILES = sources/wildcard/globing.c sources/wildcard/wildcard.c \
				sources/wildcard/tools.c    sources/wildcard/sorted_res.c \
				sources/wildcard/array_to_lst.c   sources/wildcard/search_for_names.c\
				sources/wildcard/simple_expand_red.c\
				sources/wildcard/simple_expand.c sources/wildcard/simple_expand_tools.c\
				sources/wildcard/tool_box.c sources/wildcard/searching_tools.c

FREEDOM = sources/freedom/freedom.c sources/freedom/freedom2.c sources/freedom/freedom3.c 

BUILT_TREE = sources/built_tree/builting_tools.c sources/built_tree/tree.c \
			sources/built_tree/constractors.c sources/built_tree/constractors2.c

EXECUTION = sources/execution/exec.c sources/execution/exec_pipe2.c\
			sources/execution/exec_pipe.c\
			sources/execution/exec_new.c sources/execution/signals.c\
			sources/execution/open_red2.c sources/execution/open_red.c \
			sources/execution/check_herdoc.c\
			sources/execution/exec_bonus.c sources/execution/get_precmd.c\
			sources/execution/get_cmd.c

EXPANDER = sources/expander/expander.c sources/expander/expand_list.c \
			sources/expander/utils.c sources/expander/expand_heredoc.c \
			sources/expander/tokenizer.c sources/expander/spliter.c \
			sources/expander/spliter1.c

BUILTINS = 	sources/builtins/env.c sources/builtins/lstoarry.c \
            sources/builtins/builtin.c sources/builtins/dir.c \
            sources/builtins/unset.c sources/builtins/export.c \
			sources/builtins/exit.c sources/builtins/export_utils.c \
			sources/builtins/echo.c 

CFILES =	${PARSE} \
			${BUILT_TREE} ${FREEDOM} ${ERRORS} \
			${EXPANDER} ${BUILTINS} ${EXECUTION} \
			${REDIRECTION}\
			${WILDCARD_FILES}\
			${GNL} \
			sources/one.c sources/two.c  sources/print.c \

MINISHELL_ART = \
"\033[31m\n"\
"███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n"\
"████╗ ████║ ██║ ████╗  ██║ ██║ ██║  ██║ ██╔════╝ ██║      ██║     \n"\
"██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████║ █████╗   ██║      ██║     \n"\
"██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ██╔══██║ ██╔══╝   ██║      ██║     \n"\
"██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ██║  ██║ ███████╗ ███████╗ ███████╗\n"\
"╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n"\
"						      By: TILLAS & NolYel  \033[0m"

# RLFLAGS 	=	-L/Users/aohssine/.brew/opt/readline/lib -lreadline # tell linker where to look for libs , libs to link 
# RLINCLUDE	=	-I/Users/aohssine/.brew/opt/readline/include  # tell compiler where to find headers

HEADERS = includes/minishell.h includes/builtins.h includes/colors.h  \
			includes/expander.h includes/helper.h includes/helper2.h   \
			includes/struct.h includes/norm_structs.h  

RLFLAGS =	-L/Users/ilaasri/.brew/opt/readline/lib -lreadline # tell linker where to look for libs , libs to link 
RLINCLUDE	=	-I/Users/ilaasri/.brew/opt/readline/include  #


CFLAGS = -Wall -Wextra -Werror

CC = cc
OBJ = $(CFILES:.c=.o)
NAME = minishell
My_lib = lib/libft/libft.a

all : ascii_art $(My_lib) $(NAME)

%.o : %.c  Makefile ${HEADERS}
	$(CC)  $(CFLAGS) $(FFLAG)  $(RLINCLUDE) -c  $< -o $@

$(My_lib) : 
	make -C lib/libft

$(NAME) : $(OBJ) $(My_lib) 
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r \033[0m" $@
	$(CC) $^ $(CFLAGS) $(My_lib) $(RLFLAGS)  -o $@

clean :
	@make clean -C lib/libft
	rm -rf $(OBJ)

ascii_art :
	@echo $(MINISHELL_ART)

fclean : clean
	@make fclean -C lib/libft
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re