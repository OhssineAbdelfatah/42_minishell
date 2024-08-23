#include "../includes/minishell.h"

int is_pipe(char *s)
{
    if (strlen(s) == 1 && s[0] == '|')
        return(1);
    return(0);
}

t_cmd *parse_exec(char **tokens, int *i, char **env)
{
    t_cmd *res;
    char *argv;

    // printf("argv::%s\n", "sasa");
    argv = ft_strdup(tokens[*i]);
    // printf("argv::%s\n", argv);
    res = (t_cmd *)init_exec(EXEC,argv, env);
    (*i)++;
    return( (t_cmd*)res);
}

t_cmd *parse_redirect(char **tokens, int *i, char **env)
{
    t_cmd *res;
    int fd;
    int mode;
    char *file;

    fd = 1;
    res = parse_exec(tokens, i, env);
    while (tokens[*i] && (which_one(tokens[*i]) == RED))
    {
        // write(1,"IN\n", 4);
        if ( 1 == ft_strcmp(tokens[*i], ">>"))
            mode = 77;
        else if (ft_strcmp(tokens[*i], ">"))
            mode = 7;
        else if (ft_strcmp(tokens[*i], "<"))
        {
            mode = 4;
            fd = 0;
        }
        (*i)++;
        file = ft_strdup(tokens[*i]);
        (*i)++;
        res = init_redire(res, file, mode, fd);
        // printf("\nOUT\n");
    }
    return (res);
}

struct cmd *parse_pipe(char **tokens, int *i, char **env)
{
    t_cmd *res;

    res = parse_redirect(tokens, i, env);
    while(tokens[*i] && is_pipe(tokens[*i]))
    {
        (*i)++;
        res = (t_cmd *)init_pipe(res, parse_pipe(tokens , i, env));
    }
    return (res);
    
}

t_cmd *root(char **tokens, char **env)
{
    int i = 0;
    t_cmd *res;
    // printf("creat root\n");
    res = parse_pipe(tokens, &i, env);
    printf("roottype:%d\n", res->type);
    return(res);
}
