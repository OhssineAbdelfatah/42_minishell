# include "../includes/minishell.h"

int is_white(int c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (0);
    return (1);
}

int ft_strlen1(char *s)
{
    int i = 0;
    if (s)
    {
        while (s[i])
            i++;
    }
    return (i);
}

int nbr_tokens(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (str)
    {
        while(str[i])
        {
            if (is_white(str[i]) == 1 && (is_white(str[i + 1]) == 0  || str[i + 1] == 0))
                j++;
            i++;
        }
    }
    return (j);
}

int skip_spaces(char *s, int x)
{
    if (s)
    {
        while (is_white(s[x]) == 0)
            x++;
    }
    return(x);
}

int skip_nonspaces(char *str, int i)
{
    if (str)
    {
        while (is_white(str[i]))
            i++;
    }
    return(i);
}

 char *ft_substr2(char *str, int start, int end)
{
    char *res;
    int i;
    int reslen;
    int strlen;

    i = 0;
    if (!str)
        return NULL;
    reslen = end - start;
    strlen = ft_strlen1(str);
    if (end > strlen || end < start)
        reslen = strlen - start;
    res = (char *)malloc(reslen + 1);
    if(!res)
        return(NULL);
    while(str[start] && i < reslen)
    {
        res[i++] = str[start++];
    }
    res[i] = 0;
    return (res);
}

char **tokens(char *str)
{
    char **res;
    int len,i, j;

    i = 0;
    j = 0;
    len = ft_strlen1(str);
    if (str)
    {
        i = nbr_tokens(str);
        res = (char **)malloc(sizeof(char *) * (i + 1));
        if (!res)
            return NULL;
        i = 0;
        while (i < len)
        {
            i = skip_spaces(str, i);
            if (str[i])
            {
                res[j] = ft_substr2(str, i, skip_nonspaces(str, i));
                j++;
            }
            i = skip_nonspaces(str, i);

        }
        res[j] = 0;
    }else
        res = NULL;
    return (res);
}




// int main(int ac , char **av, char **envp)
// {
    
//     char *cmd = "./alo";
//     char **argv ;
//     // argv[0] = "..";
//     // char **s={"ls", "-l", NULL};
//     execve(cmd,argv , NULL);
// }