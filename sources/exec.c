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

void execute_cmd(t_cmd *cmd,__unused t_io *io)
{
    struct exec_cmd *p;
    char ** cmd_args;
    // char ** argv;
    char *ss;

    // pid_t pid;  
    p = (struct exec_cmd *)cmd;
    ss = cmd_abs_path(getenv("PATH"), ft_strdup(p->argv));
    if(!ss)
        panic("Error : command not found\n");
    cmd_args = ft_split(p->argv, 32);
    // argv = ft_split(ss, 32);

    // builtin(cmd_args, p);
    // free(ss);
    // ss = NULL;
    // if (dstr_len(cmd_args))
    //     ss = ft_strjoin("/usr/bin/",cmd_args[0]);

    printf("exec %s in{%d} out{%d}\n", ss, io->in, io->out);   
    // pid = fork();
    // if(0 == pid)
    // {
        // if(io->out != 1 )
        //     dup2(io->out, 1);
        // if(io->in != 0 )
        //     dup2(io->in, 0);
        if( -1 == execve(ss, cmd_args,p->env))
        {
            free(ss);
            panic("minishell : command not found\n");
            exit(0);
            // ss = ft_strdup(cmd_args[0]);
            // if (-1 == execve(ss, cmd_args + 1,p->env))
        }
        else    
            printf("giiiiid\n");
    // }
    // wait(0);
    free_mynigga(cmd_args);
    free(ss);
    return;
}

void execute_red (t_cmd *cmd)
{
    struct red *p;
    t_io io;
    p = (struct red *)cmd;
    close(p->fd);
    printf("type %d,mode %d, file %s \n",p->type, p->mode, p->file);
    if(open(p->file, O_CREAT | O_RDWR | O_APPEND , 777) < 0){
    //   fprintf(2, "open %s failed\n", p->file);
        panic("execred\n");
      exit(1);
    }
    exec(p->cmd, &io);
}


void execute_pipe (t_cmd *cmd, t_io *io)
{
    struct pipe *pcmd;
    int p[2]; // this sould pass to left and right node
    // 0 read
    int t;
    int y;
    // 1 write

    pcmd = (struct pipe *)cmd;
    printf("exec PIPE\n");    
    io->in = 0;
    io->out = 1;
    pipe(p);
    printf("in{%d} out{%d}\n",p[0] ,p[1]);
    if((t = fork()) == 0){
      close(p[0]);
      dup2(p[1],1);
      close(p[1]);
      io->out = p[1];
        printf("before left in{%d} out{%d}\n",io->in ,io->out);
      exec(pcmd->left, io);
    //   exit(0);
    }
    // wait(0);
    if((y = fork()) == 0){
      close(p[1]);
      dup2(p[0],0);
      close(p[0]);
      io->out = p[0];
        printf("before right in{%d} out{%d}\n",io->in ,io->out);
      exec(pcmd->right, io);
    //   exit(0);
    }
    close(p[0]);
    close(p[1]);
    wait(&t);
    wait(&y);
    // while (wait(0) == -1);

}

void exec(t_cmd *cmd, t_io *io)
{
    // write(1, "exec IN\n", 9);
    if (!cmd)
        return;
    else if (cmd->type == EXEC)
        execute_cmd (cmd, io);
    else if (cmd->type == PIPE)
        execute_pipe(cmd, io);
    else if (cmd->type == RED)
        execute_red (cmd );
    // write(1, "exec OUT\n", 10);
}

// void exec(t_cmd *cmd)
// {
//     t_cmd *tmp;

//     tmp = cmd;
//     while(tmp.)
// }


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
