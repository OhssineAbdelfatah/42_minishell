/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:54:30 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:54:32 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**check_empty_ones(char **old, char **ancient)
{
	t_check_empty_ones	var;

	var.i = 0;
	var.oldlen = dstr_len(old);
	if (var.oldlen == 0)
		return (old);
	var.old_clone = unquote_old(old, 0);
	while (var.old_clone[var.i] && ft_strlen(var.old_clone[var.i]) == 0
		&& NULL != ft_strchr(ancient[var.i], '$'))
		var.i++;
	if (var.i == 0)
		return (free_dawgs(2, var.old_clone, ancient), old);
	if (var.i == var.oldlen)
		return (free_dawgs(3, old, var.old_clone, ancient), NULL);
	var.reslen = var.oldlen - var.i;
	var.res = malloc(sizeof(char *) * (var.reslen + 1));
	if (!var.res)
		panic("malloc failed\n");
	var.j = 0;
	while (var.j < var.reslen)
		var.res[var.j++] = ft_strdup(old[var.i++]);
	var.res[var.j] = NULL;
	free_dawgs(3, old, var.old_clone, ancient);
	return (var.res);
}

int	is_it_wild_args(char **av)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!av)
		return (0);
	while (av[i])
	{
		if (is_it_wild(av[i]))
			ret++;
		i++;
	}
	return (ret);
}

int	is_it_wild(char *av)
{
	int	i;
	int	avlen;

	i = 0;
	avlen = ft_strlen(av);
	if (!av)
		return (0);
	while (av[i])
	{
		if (av[i] == '/' && i != avlen - 1)
			return (0);
		if (av[i] == '\'' || av[i] == '"')
			i = get_next_quote(av, i);
		if (av[i] == '*')
			return (1);
		if (av[i])
			i++;
	}
	return (0);
}

char	*in_which_dir(char *s)
{
	int		slen;
	char	*work_dir;

	work_dir = NULL;
	if (ft_strchr(s, '/'))
	{
		slen = ft_strlen(s);
		while (slen >= 0)
		{
			if (s[slen] == '/')
				break ;
			slen--;
		}
		return (ft_substr(s, 0, slen + 1));
	}
	work_dir = getcwd(work_dir, 256);
	return (work_dir);
}

// void treat_wild(char **ret, char *old_arg, int *j)
// {
//     char *dir_name;

//     dir_name = in_which_dir(old_arg);
//     if (valid_dir(dir_name))
//         return ;
//     (void)ret;
//     (void)old_arg;
//     (void)j;
//     (void)dir_name;
// }

// int lenofminiwild(char *arg)
// {
//     int i;
//     int ret;

//     ret = 0;
//     i = 0;
//     while (arg[i])
//     {
//         if (arg[i] == '/')
//             ret++;
//         i++;
//     }
//     return (ret);
// }

// int get_retlen(char **old_arg)
// {
//     int i;
//     int ret;

//     ret = 0;
//     i = 0;
//     while (old_arg[i])
//     {
//         if (is_it_wild(old_arg[i]))
//             ret = lenofminiwild(old_arg[i]);
//         else
//             ret ++;
//         if (ret < 0)
//             return (ret);
//         i++;
//     }
//     return (ret);
// }

// char **new_args(char **old_arg)
// {
//     int i, j;
//     char **ret;
//     int retlen;

//     i = 0;
//     j =0;
//     retlen = get_retlen(old_arg);
//     if (retlen <= 0)
//         return (old_arg);
//     ret = (char **)malloc(sizeof(char *) * (retlen + 1));
//     if (!ret)
//         return (NULL);
//     while(old_arg[i])
//     {
//         ret[j] = ft_strdup(old_arg[i]);
//         if(is_it_wild(old_arg[i]))
//             treat_wild(ret, old_arg[i], &j);
//         i++;
//         j++;
//     }
//     free_mynigga(old_arg);
//     return (ret);
// }

// void	print_to_expand(char **av)
// {
// 	int	i;

// 	i = 0;
// 	while (av[i])
// 	{
// 		printf("arg[%d] :%s ,to expand : %d\n", i + 1, av[i],
// 			is_it_wild(av[i]));
// 		i++;
// 	}
// }

// int main(int ac , char **av)
// {
//     if (ac != 2)
//         return (1);
//     printf("the ARG :  %s\n", av[1]);
//     printf("is wild >> %d\n", is_it_wild(av[1]));
//     return(0);
// }
