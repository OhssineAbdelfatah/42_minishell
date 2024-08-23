#include "../includes/minishell.h"

// int parse(char *str)
// {
//     int i = 0;
//     while (str[i])
//     {
//         i = skip_spaces(str, i);

//         i++;
//     }

// }



int check_qoutes(char *s)
{
    int i;
    enum ss j;

    i = 0;
    j = NONE;
    if (s)
    {
        while(s[i])
        {
            if(s[i] == '"')
                if (j == SINGLE)
                    j = SINGLE;
                else if (j == DOUBLE)
                    j = NONE;
                else
                    j = DOUBLE;
            if(s[i] == '\'')
                if (j == DOUBLE)
                    j = DOUBLE;
                else if (j == SINGLE)
                    j = NONE;
                else
                    j = SINGLE;
    
            i++;
        }
    }
    return(j);
}

void panic(char *str)
{
    if (str);
        dprintf(2, str);
    exit(1);
}

void free_mynigga(char **str)
{
    int i = 0;
    // printf("i am abt to free\n");
    if (str)
    {
   
        while (str[i])
        {
            // printf("free%d\n",i);
            free(str[i]);
            str[i] = NULL;
            // ft_putnbr_fd(i,1);
            i++;
        }
    }
    free(str);
    str = NULL;
    // printf("done free\n");
}


int main(int ac, char **av, char **env)
{
    char *str, *str1;
    char **my_tokens;
    t_cmd *res;
    int i = 0;
    while(1)
    {
        str = readline("depechez-vous!> ");
        // str = ft_strdup(str1);
        add_history(str);
        my_tokens = NULL;
        if (0 !=_check_str(str))
            panic("error from the main\n");
        else if (ft_strlen(str))
        {
            i = 0;
           
            my_tokens = split_shit(str);
             
            res = root(my_tokens,env);
            print_tree(res);
            // write(1, "main IN\n", 9);
            printf("\n");
            exec(res);
            free_tree(res);
            free_mynigga(my_tokens);

            // printf("RED is :%d\n", RED);
            // while(my_tokens[i])
            // {
            //     // printf("adres of tok:%p, what it point to:%p\n", &my_tokens[i], &(*my_tokens[i]));
            //     printf("that's your command >>:%s:\n", my_tokens[i++]);
            // }
            // exec_cmd(my_tokens, env);

            // write(1, "main OUT\n", 10);
        }
        free(str);
    }
}
