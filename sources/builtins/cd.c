#include"../../includes/minishell.h"

int ft_strslen(char **strs)
{
    int i = -1;
    if(!strs || !(*strs))
        return 0;
    while(strs[++i]);
    return i;
}

void free_split(char **str)
{
    int i = -1;
    while(str[++i])
        free(str[i]);
    free(str);
    return ;
}
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
            return -1;
        chdir(cmd_arg[1]);
    }
     return 0;   
}

// int cd(t_cmd *cmds)
// {
//     struct exec_cmd *p = (struct exec_cmd *)cmds;
//     int j = 0;
//     int i = 0;
//     char *env_path;
//     char *change_to = NULL;

//     while(cmd[++j]);
//     if(j != 0){
//         while(cmd[++i])
//         {
//             if(access(cmd[i], R_OK) == 0)
//                 change_to = cmd[i];
//         }
//         if(!change_to)
//             perror("mkynch directory");
//         if(chdir(change_to) == -1){
//             perror("chdir failed1");
//             return -1;
//         }
//     }else{
//         env_path = getenv("HOME");
//         if(env_path == NULL)
//             return -1; 
//         if(chdir(env_path) == -1){
//             perror("chdir failed0");
//             return -1;
//         }
//     }
//     return 0;
// }