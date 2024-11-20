/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_expand_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:53:54 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:53:56 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	freedom(char ***dir_cont_array, t_dir_cont **dir_cont, char **working)
{
	free_mynigga(*dir_cont_array);
	free_dir_lst(dir_cont);
	free(*working);
}

char	*get_next_valid(t_dir_cont *dir_cont, int index)
{
	int			i;
	t_dir_cont	*tmp;
	char		*res;

	i = 0;
	tmp = dir_cont;
	res = NULL;
	while (tmp)
	{
		if (tmp->valid == 1 && index == i)
		{
			res = ft_strdup(tmp->value);
			return (res);
		}
		else if (tmp->valid == 1)
			i++;
		tmp = tmp->next;
	}
	return (res);
}

char	*get_work_direc(void)
{
	char	*work_dir;
	char	*last;

	work_dir = NULL;
	work_dir = getcwd(work_dir, 256);
	last = ft_strjoin(work_dir, "/");
	free(work_dir);
	return (last);
}

char	**unquote_old(char **old, int to_free)
{
	int		i;
	int		res_len;
	char	**res;

	i = 0;
	res_len = dstr_len(old);
	res = (char **)malloc(sizeof(char *) * (res_len + 1));
	if (!res)
		panic("malloc failed \n");
	while (i < res_len)
	{
		res[i] = whithout_quotes(old[i], to_free);
		i++;
	}
	res[i] = NULL;
	if (to_free)
	{
		free(old);
		old = NULL;
	}
	return (res);
}

char	*take_slash_of(char *arg)
{
	int		i;
	int		newlen;
	char	*new;

	i = 0;
	newlen = ft_strlen(arg) - 1;
	if (arg[newlen] != '/')
		return (arg);
	new = (char *)malloc(newlen + 1);
	if (!new)
		panic("malloc failed!\n");
	while (i < newlen)
	{
		new[i] = arg[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

// void	printd(char **av)
// {
// 	int	i;

// 	i = 0;
// 	while (av[i])
// 		printf("AV :: %s\n", av[i++]);
// }

// void	print_valid_ones(t_dir_cont *head)
// {
// 	t_dir_cont	*tmp;

// 	tmp = head;
// 	while (tmp)
// 	{
// 		if (tmp->valid == 1)
// 			printf("VALID ONE :%s\n", tmp->value);
// 		tmp = tmp->next;
// 	}
// }