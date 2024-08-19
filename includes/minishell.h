#ifndef MINISHELL_H

#define MINISHELL_H
#include<stdio.h>
#include"libft/libft.h"
#include<unistd.h>
typedef struct s_token t_token;
struct s_token
{
    char *token_value;
    t_token *left;
    t_token *right;
    t_token *parent;
} ;


/***
 * Prototypes
***/

/*
 builtins 
*/
void cd(void);


// int executer();


#endif
