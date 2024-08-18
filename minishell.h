#ifndef MINISHELL_H

#define MINISHELL_H
#include<stdio.h>

typedef struct s_token
{
    char *token_value;
    t_token *left;
    t_token *right;
    t_token *parent;
} t_token;


void cd(char *path);
int executer();


#endif
