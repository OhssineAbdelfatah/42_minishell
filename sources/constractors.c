#include "../includes/minishell.h"


t_cmd *init_exec(int tp, char *s, char **env)
{
    struct exec_cmd *res;

    res = malloc(sizeof(struct exec_cmd));
    if(!res)
        panic("init_exec\n");
    res->type = tp;
    res->argv = s;
    res->env = env;
    return((t_cmd *)res);
}

t_cmd *init_pipe(t_cmd *left, t_cmd *right)
{
    struct pipe *res;

    res = malloc(sizeof(*res));
    if (!res)
        panic("init_pipe\n");
    res->type = PIPE;
    res->left = left;
    res->right = right;
    return ((t_cmd *)res);
}

t_cmd *init_redire(t_cmd *cmd, char *file , int mode, int fd)
{
    struct red *res;
    t_cmd *final;

    res = malloc(sizeof(*res));
    if (!res)
        panic("init_redirect\n");
    res->cmd = cmd;
    res->mode = mode;
    res->file = file;
    res->fd = fd;
    res->type = RED;
    final = (t_cmd *)res;
    return (final);
}


t_cmd *init_herdoc(t_cmd *cmd, char *deliminater)
{
    struct heredoc *res;
    res = malloc(sizeof(*res));
    if (!res)
        panic("init_herdoc\n");
    res->type = HERDOC;
    res->cmd = cmd;
    res->delimiter = deliminater;
    return ((t_cmd*)res);
}