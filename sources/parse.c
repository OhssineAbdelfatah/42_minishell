#include "../includes/minishell.h"

int get_next_quote(char *s,int i)
{
    if (s[i] == '"')
    {
        i++;
        while(s[i] && s[i] != '"')
            i++;
    }
    else
    {
        i++;
        while(s[i] && s[i] != '\'')
            i++;
    }
    return i;
}

int which_one(char *s)
{
    t_typenode i;
    if (!s)
        return -1;
    if (ft_strlen(s) == 2)
    {
        if (ft_strcmp(s, "<<"))
            return (i = HERDOC);
        if (ft_strcmp(s,">>"))
            return (i = RED);
    }
    if (s[1] == '\0' && (s[0] == '>' || s[0] == '<'))
        i = RED;
    else if (s[0] == '|')
        i = PIPE;
    else if (s[0] == '$')
        i = ENV_VAR;
    return(i);
}

int is_special(char s)
{
    int i;
    char *symbols = "<|>";

    i = 0;
    if(s)
    {
        while(symbols[i])
        {
            if(symbols[i] == s)
                return (1);
            i++;
        }
    }
    return(0);
}

int count_tokens(char *s)
{
    int i , j;
    int res;

    i= j= 0;
    res =  0;
    if (s)
    {
        while(s[i])
        {
            i = skip_spaces(s, i);
            if (s[i] && (1 == is_special(s[i])) && (j >= 0))
            {
                j = -1;
                res++;
                while (s[i] &&  (1 == is_special(s[i])))
                {
                    if (s[i] == '\''|| s[i] == '"')
                        i = get_next_quote(s, i);
                    i++;
                }
            }
            i = skip_spaces(s, i);
            if (s[i] && (0 == is_special(s[i])) && j <= 0)
            {
                j = 1;
                res++;
                while (s[i] &&  (0 == is_special(s[i])))
                {
                    if (s[i] == '\''|| s[i] == '"')
                        i = get_next_quote(s, i);
                    i++;
                }
            }
        }
    }
    return (res);

}

int next_nonspecial(char *s, int i)
{
    while(s[i] && is_special(s[i]))
        i++;
    return (i);
}

int get_start(char *s, int i)
{
    if (s)
    {
        if (s[i] == 32 || (s[i] <= 13 && s[i] >= 9))
            return(skip_spaces(s, i));
        else 
            return (i);
    }
   return(i);
}


int get_end(char *s, int i)
{
    int j;
    if (is_special(s[i]))
        return(next_nonspecial(s, i));
    else
    {
        while (s[i] && !is_special(s[i]))
        {
            if (s[i] == '\''|| s[i] == '"')
                i = get_next_quote(s, i);
            i++;
            if (is_special(s[i]) && s[i - 1] == 32 || (s[i - 1] <= 13 && s[i - 1] >= 9))
            {
                i--;
                while ( i > 0 && s[i] == 32 || (s[i]<= 13 && s[i] >= 9))
                    i--;
                i++;
                return(i);
            }
        }
    }
    return(i);
}

char **split_shit(char *s)
{
    int i = 0;
    int start;
    int end;
    char **res;
    int reslen;

    if (!s)
        return(NULL);
    start =skip_spaces(s,i);
    reslen = count_tokens(s);
    if (!reslen)
        return (NULL);
    res = (char **)malloc(sizeof(char *) *  (reslen + 1));
    if (!res)
        return(NULL);
    while(i < reslen)
    {
        end = get_end(s, start);
        res[i] = ft_substr(s, start, end - start);
        start = get_start(s, end );
        i++;
    }
    res[i] = NULL;
    return (res);    
}


int _check_str(char *s)
{
    int i = 0;
    if (s)
    {
        if (check_qoutes(s))
            panic("quotes\n");
        while(s[i])
        {
            if (s[i] == '|' && s[i + 1] == '|')
                panic("||\n");
            if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<')
                panic("<<<\n");
            if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>')
                panic(">>>\n");
            else
                i++;
        }
        return(0);
    }
    return(1);
}
