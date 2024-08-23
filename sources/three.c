#include "../includes/minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i, j, s2len;

    i = 0;
    j = 0;
    s2len = ft_strlen1(s2);
    if (!s1 || !s2)
        return (0);
    else
    {
        while(i < s2len)
        {
            if (s1[i] != s2[i])
                return(0);
            i++;
        }
    }
    return(1);
}

void _cd(char *s)
{
    char **res = ft_split(s, 32);
}

void check_builtIn(char *s)
{
    if (ft_strcmp(s, "exit"))
        panic("exit\n");
    else if (ft_strcmp(s, "cd"))
        _cd(s);
}

void exec_cmd(char **tokens, char **env)
{
    int i;
    i= 0;
    if (!tokens)
        return;
    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "exit"))
        {
            printf("it is exit command!\n");
            exit(1);
        }
        else
        {
            pid_t  pid = fork();
            if (pid == -1)
            {
                printf("\nCOULD not execute command \n");
                return; 
            }
            else if(pid == 0)
            {
                if (-1 == execve(ft_strjoin("/usr/bin/", tokens[i]), NULL, env))
                    panic("minishell : command not found\n");
            }
            else
                wait(NULL);
        }
        i++;
    }
}
