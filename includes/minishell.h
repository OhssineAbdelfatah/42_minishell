#ifndef MINISHELL_H

#define MINISHELL_H
#include<stdio.h>
#include"./libft/libft.h"
#include<unistd.h>
typedef struct s_token t_token;

// aohssine
struct s_token
{
    char *token_value;
    char *cmd;
    t_token *left;
    t_token *right;
    t_token *parent;
} ;

/*ilaasri*/
typedef struct cmd t_cmd;

typedef enum ss
{
    NONE,
    SINGLE,
    DOUBLE
}ss;

typedef enum typenode
{
    EXEC,
    PIPE,
    REDIRECT,
    HERDOC,
    ENV_VAR,
    NONE_NODE
} t_typenode;


struct cmd
{
    int type;
};

struct exec_cmd
{
    int type;
    char argv;
};

struct pipe
{
    int type;
    struct cmd *left;
    struct cmd *right;
};

struct redirect
{
    int type;
    struct cmd *cmd;
    char file;
    int mode;
    int fd;
};

struct heredoc {
    int type;
    struct cmd  *cmd;
    char *delimiter;
    char *content; 
};
// executer 
/*
    take a t_cmd based on its type ,
    i should cast to (herdoc , redirect, pipe , none_node , Env_Var)
*/
/* ilaasri */

/***
 * Prototypes
***/


/*
 builtins 
*/
void cd(void);


// int executer();


#endif
