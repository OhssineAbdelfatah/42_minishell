/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:54:13 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:54:15 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_len_of_dir(char *dir_name)
{
	DIR				*dir;
	struct dirent	*po;
	int				res;

	dir = opendir(dir_name);
	if (!dir)
		return (-1);
	res = 0;
	while (1)
	{
		po = readdir(dir);
		if (!po)
			break ;
		res++;
	}
	closedir(dir);
	return (res);
}

int	file_or_dir(char *s)
{
	if (s[ft_strlen(s) - 1] == '/')
		return (DIREC);
	return (ALL_KINDS);
}

int	valid_interval(char *val)
{
	if (val[1] > val[3])
		return (0);
	return (1);
}

int	valid_dir(char *dir_nmae)
{
	DIR	*di;

	di = opendir(dir_nmae);
	if (NULL == di)
		return (0);
	closedir(di);
	return (1);
}

int	how_many_wild(char *av)
{
	int	i;
	int	index;
	int	ret;

	ret = 0;
	i = 0;
	while (av[i])
	{
		if (av[i] == '*' && index == 0)
		{
			ret++;
			index = 1;
		}
		if (av[i] == '/')
			index = 0;
		i++;
	}
	return (ret);
}
