#ifndef HELPER_H
# define HELPER_H

#include "struct.h"

void free_mynigga(char **str);
void free_tree(t_cmd *cmd);

struct cmd *init_pipe(t_cmd *left, t_cmd *right);
struct cmd *init_exec(int tp, char *s, char **env);
struct cmd *init_redire(t_cmd *cmd, char *file , int mode, int fd);
t_cmd *init_herdoc(t_cmd *cmd, char *deliminater);
char **tokens(char *str);
int _check_str(char *s);
int check_qoutes(char *s);
t_cmd *root(char **tokens, char **env);
void print_tree(t_cmd *res);
int which_one(char *s);
// int skip_nonspaces(char *str, int i);
//  char *ft_substr(char *str, int start, int end)

# endif