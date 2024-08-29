# ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>

#include "helper.h"
#include "struct.h"
#include "libft/libft.h"


int ft_strcmp(char *s1, char *s2);
int skip_spaces(char *s, int x);
void exec_cmd(char **tokens, char **env);
void panic(char *str);
int ft_strlen1(char *s);
char **split_shit(char *s);
void exec(t_cmd *cmd);


# endif