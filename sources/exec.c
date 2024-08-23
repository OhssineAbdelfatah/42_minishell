#include "../includes/minishell.h"


// void builtin(char **str, struct exec_cmd *p)
// {
//         _cd_cmd(str, p);
//     else if (ft_strcmp(str[0], "echo"))
//         _echo_cmd(str, p);
//     else if (ft_strcmp(str[0], "exit"))
//         panic("BY!");
//     else if (ft_strcmp(str[0], ""))
//         _export_cmd (str, p);
// }

int dstr_len(char **s)
{
    int i;

    i = 0;

    if (s)
    {
        while(s[i])
            i++;
    }
    return(i);
}

void execute_cmd(t_cmd *cmd)
{
    struct exec_cmd *p;
    char **str;
    char **argv;
    char *ss;
    pid_t pid;

   
    p = (struct exec_cmd *)cmd;
    ss = ft_strdup(p->argv);
    if(!ss)
        return;
    str = ft_split(ss, 32);
    argv = ft_split(ss, 32);
    // builtin(str, p);
    free(ss);
    ss = NULL;
    if (dstr_len(str))
        ss = ft_strjoin("/usr/bin/",str[0]);
    pid = fork();
    if(0 == pid)
    {
        if( -1 == execve(ss, str++,p->env))
        {
            free(ss);
            ss = ft_strdup(argv[0]);
            if (-1 == execve(ss, argv++,p->env))
                panic("minishell:command not found\n");
        }
        free_mynigga(argv);
        free(ss);
        ss = NULL;
    }
    wait(0);
    return;
}

void execute_red (t_cmd *cmd)
{
    struct red *p;

    p = (struct red *)cmd;
    close(p->fd);
    if(open(p->file, p->mode) < 0){
    //   fprintf(2, "open %s failed\n", p->file);
        panic("execred\n");
      exit(1);
    }
    exec(p->cmd);
}


void execute_pipe (t_cmd *cmd)
{
    struct pipe *pcmd;
    int p[2];

    pcmd = (struct pipe *)cmd;

    if(fork() == 0){
      close(1);
      dup(p[1]);
      close(p[0]);
      close(p[1]);
      exec(pcmd->left);
    }
    if(fork() == 0){
      close(0);
      dup(p[0]);
      close(p[0]);
      close(p[1]);
      exec(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait(0);
    wait(0);
    printf("exec PIPE\n");

    
}

void exec(t_cmd *cmd)
{
    // write(1, "exec IN\n", 9);
    if (!cmd)
        return;
    else if (cmd->type == EXEC)
        execute_cmd (cmd);
    else if (cmd->type == PIPE)
        execute_pipe(cmd);
    else if (cmd->type == RED)
        execute_red (cmd);
    // write(1, "exec OUT\n", 10);
}



void free_cmd(t_cmd *cmd)
{
    struct exec_cmd *p;

    p = (struct exec_cmd *)cmd;
    free(p->argv);
    p->argv = NULL;
    free(p);
    p = NULL;
}

void free_pipe(t_cmd *cmd)
{
    struct pipe *p;

    p = (struct pipe *)cmd;
    free_tree(p->left);
    free_tree(p->right);
    free(p);
    p = NULL;
}

void free_red(t_cmd *cmd)
{
    struct red *p;

    p = (struct red *)cmd;
    free(p->file);
    p->file = NULL;
    free_tree(p->cmd);
    free(p);
    p = NULL;
}

void free_tree(t_cmd *cmd)
{
    if (!cmd)
        return;
    if (cmd->type == EXEC)
        free_cmd (cmd);
    else if (cmd->type == PIPE)
        free_pipe(cmd);
    else if (cmd->type == RED)
        free_red (cmd);
}
