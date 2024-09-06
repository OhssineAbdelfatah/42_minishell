#include"../../includes/minishell.h"

void add_back_env(t_env **head, t_env*node)
{
    t_env *tmp;

    if(!head )
        return;
    if(!(*head)){
        *head = node;
        return ;
    }
    tmp = *head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
}

t_env *creat_env(char **pair)
{
    t_env *node;
    
    node = malloc(sizeof(t_env));
    if(!node)
        return NULL;
    node->key = ft_strdup(pair[0]);
    if(ft_strslen(pair) == 2)
        node->value = ft_strdup(pair[1]);
    else
        node->value = NULL;
    node->next = NULL;
    return node;
}

t_env *init_env(char **env_main)
{
    t_env *env;
    t_env *tmp;
    char **pair;
    int i = -1;
    env =NULL;
    while(env_main[++i]){
        pair = ft_split(env_main[i], '=');
        // printf("%s=%s\n",pair[0], pair[1]);
        tmp = creat_env(pair);
        add_back_env(&env,tmp);
        free_split(pair);
        pair =NULL;
    }
    return env;
}

void print_env(t_env *env)
{
    while(env->next != NULL)
    {
        if(env->key)
            printf("%s",env->key);
        printf("=");
        if(env->value)
            printf("%s",env->value);
        printf("\n");
        env = env->next;
    }
}

// int main(__unused int ac, __unused char **av, char *env[])
// {

//     t_env myenv;
//     myenv = *init_env(env);
//     print_env(&myenv);
// }