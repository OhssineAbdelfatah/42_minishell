/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:54:03 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:54:04 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**all_dir_sorted(char *dir_name)
{
	t_dir_cont_array	var;

	var.i = 0;
	var.retlen = get_len_of_dir(dir_name);
	if (var.retlen <= 0)
		return (NULL);
	var.ret = (char **)malloc(sizeof(char *) * (var.retlen + 1));
	if (!var.ret)
		panic("malloc failed!\n");
	var.dir = opendir(dir_name);
	while (var.i < var.retlen)
	{
		var.po = readdir(var.dir);
		var.ret[var.i] = ft_strdup(var.po->d_name);
		if (!var.ret[var.i])
			panic("malloc failed!\n");
		var.i++;
	}
	var.ret[var.i] = NULL;
	closedir(var.dir);
	just_sort(var.ret);
	return (var.ret);
}

int	skip_dot(char *s, int i)
{
	while (s[i] && ft_isalpha(s[i]) == 0)
		i++;
	return (i);
}

int	need_a_sort(char *a, char *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a[i])
	{
		if ((a[i]) > (b[j]))
			return (-1);
		if ((a[i]) < (b[j]))
			return (0);
		i++;
		j++;
	}
	return (0);
}

int	is_it_sorted(char **dir)
{
	int	i;

	i = 0;
	while (dir[i])
	{
		if (dir[i + 1] == NULL)
			break ;
		if (need_a_sort(dir[i], dir[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

void	just_sort(char **dir)
{
	int	i;

	i = 0;
	while (is_it_sorted(dir))
	{
		while (dir[i])
		{
			if (dir[i + 1] == NULL)
				break ;
			if (need_a_sort(dir[i], dir[i + 1]))
				ft_swap_str(&dir[i], &dir[i + 1]);
			i++;
		}
		i = 0;
	}
}
