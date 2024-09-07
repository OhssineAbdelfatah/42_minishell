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

char *cmd_abs_path(char *path,char *cmd)
{
    char **path_2d;
    char *cmd_abs_path;

    path_2d = ft_split(path, ':');
    int i = -1;
    cmd_abs_path = *ft_split(ft_strdup(cmd), 32);

    int j = -1 ;
	while(path_2d[++j])
		path_2d[j] = ft_strjoin(path_2d[j], "/");
    while(path_2d[++i])
    {
        if(access(ft_strjoin( path_2d[i], cmd_abs_path), X_OK) == 0)
        {
            cmd_abs_path = ft_strjoin( path_2d[i], cmd_abs_path);
            // free var(path2d)
            return cmd_abs_path;
        }
    }
    return NULL;
}

void execute_cmd(t_cmd *cmd)
{
    struct exec_cmd *p;
    p = (struct exec_cmd *)cmd;
    int pid ;
    char ** cmd_args;
    char *ss;
    if(is_builtin(cmd))
    {
        exec_builtin(cmd);
        return ;
    }
    cmd_args = ft_split(p->argv, 32);
    ss = cmd_abs_path(getenv("PATH"), ft_strdup(p->argv));
    if(!ss)
        panic("Error : command not found\n");
    pid = fork();
    if(pid == 0)
    {
        if( -1 == execve(ss, cmd_args,p->env))
        {
            free(ss);
            panic("minishell : command not found\n");
            return;
        }
        else    
            printf("giiiiid\n");
    }
    wait(0);
    free_mynigga(cmd_args);
    free(ss);
    return;
}

void execute_red (t_cmd *cmd)
{
    struct red *p;
    int new_fd= 0;
    p = (struct red *)cmd;
    int pid = fork();
    if (pid == 0)
    {
        close(p->fd);
        printf("type %d,mode %d, file %s \n",p->type, p->mode, p->file);
        if(p->mode == 7)
            new_fd = open(p->file, O_CREAT | O_RDWR | O_TRUNC , 0777);
        else if(p->mode == 77)
            new_fd = open(p->file, O_CREAT | O_RDWR | O_APPEND , 0777);
        if(new_fd < 0){
            panic("execred\n");
            exit(1);
        }
        dup2(p->fd, new_fd);
        close(new_fd);
        exec(p->cmd);
        exit(0);
    }
	wait(0);
}


void execute_pipe (t_cmd *cmd)
{
    struct pipe *pcmd;
    pcmd = (struct pipe *)cmd; // typecast to pipe struct

    int p[2];
    pipe(p);

    int pleft;
    int pright;
    if((pleft = fork()) == 0){
        close(p[0]);
        dup2(p[1],1);
        close(p[1]);

    }
    // wait(0);
    if((pright = fork()) == 0){
        close(p[1]);
        dup2(p[0],0);
        close(p[0]);
        exec(pcmd->right);
    }
    close(p[0]);
    close(p[1]);

}

void exec(t_cmd *cmd)
{
    // write(1, "exec IN\n", 9);
    if (NULL == cmd)
        return;
    else if (cmd->type == EXEC)
        execute_cmd(cmd);
    else if (cmd->type == PIPE)
        execute_pipe(cmd);
    else if (cmd->type == RED)
        execute_red (cmd );
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
