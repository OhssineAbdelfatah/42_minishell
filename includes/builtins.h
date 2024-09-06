#ifndef BUILTINS_H
# define BUILTINS_H

#include "struct.h"


void execute_cmd(t_cmd *cmd);
int exec_builtin(t_cmd *cmd);
bool is_builtin(t_cmd *cmd);
/*  CD  */
int cd(t_cmd *cmd);


/*  ENV  */

void add_back_env(t_env **head, t_env*node);
t_env *init_env(char **env_main);
void print_env(t_env *env);
t_env *creat_env(char **pair);

# endif