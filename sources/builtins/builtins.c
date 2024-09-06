#include"../../includes/minishell.h"

bool check_files(char **files)
{
    int i = 0;
    while(files[++i]){
        if(access(files[i], R_OK | X_OK | W_OK) != 0)
            return false;
    }
    return true;
}
int pwd(t_cmd *cmd){
    struct exec_cmd *p;
    p = (struct exec_cmd *)cmd;
    char *curd = NULL;
    printf("%s\n",getcwd(curd, 1024));
    return 0;
}

int cd(t_cmd *cmd)
{
   // i shoudld handle
   /*
   - : chdir to OLDPWD env variable if setted
   ~ : chdir to HOME env variable
   arg : pass directly to chdir
   */
    // char *curd = NULL;
    // cast to exec_cmd
    // printf("%s\n",getcwd(curd,1024));
    struct exec_cmd *p;
    p = (struct exec_cmd *)cmd;
    char *arg;
    char **cmd_arg = ft_split(p->argv, 32);
    p = (struct exec_cmd *)cmd;
    // cd only without args
    if(ft_strslen(cmd_arg) == 1){ 
        if( !(arg = getenv("HOME")) )
            return -1;
        chdir(arg);
    }else
    {
        if(access(cmd_arg[1], R_OK) != 0)
            return (panic("not found\n"),-1);
        chdir(cmd_arg[1]);
    }
     return 0;   
}

bool is_builtin(t_cmd *cmd)
{
    struct exec_cmd *p = (struct exec_cmd *)cmd;
    char *bcmds[] = {"cd","pwd", "export","unset","env","exit","echo"};
    char **cmd_arg = ft_split(p->argv, 32);
    int i = -1;
    while(++i < 7)
    {
        if(ft_strcmp(cmd_arg[0], bcmds[i]) == 0 )
        {
            free_split(cmd_arg);
            return true;
        }
    }
    return false;
}

int exec_builtin(t_cmd *cmd)
{
    struct exec_cmd* p ;
    p = (struct exec_cmd*)cmd;
    char **cmd_arg;
    cmd_arg = ft_split(p->argv, 32);
    if(!cmd_arg || !(*cmd_arg))
        return -1;
    if(ft_strcmp(cmd_arg[0], "cd"))
        cd(cmd);
    else if(ft_strcmp(cmd_arg[0], "pwd"))
        pwd(cmd);
    else if(ft_strcmp(cmd_arg[0], "env")){
        t_env ennv = *(init_env(p->env));
        print_env(&ennv);
    }
    free_split(cmd_arg);
    return 0;
}