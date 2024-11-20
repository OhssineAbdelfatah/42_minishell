/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:20:12 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 22:20:14 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_last(char *needl, char *haystak, int i)
{
	int	stacklen;
	int	needlen;

	needlen = ft_strlen(needl);
	stacklen = ft_strlen(haystak);
	while (needlen >= 0)
	{
		if (stacklen < 0)
			return (1);
		if (needl[needlen] != haystak[stacklen])
			return (1);
		if (stacklen < i)
			break ;
		stacklen--;
		needlen--;
	}
	if (needlen == -1)
		return (0);
	return (1);
}

int	check_midd(char *needle, char *haystack, int *start, int *index)
{
	int	i;
	int	j;

	i = *start;
	j = 0;
	while (haystack[i])
	{
		while (needle[j] && haystack[i + j] && haystack[i + j] == needle[j])
			j++;
		if (j == (int)ft_strlen(needle))
		{
			*start = i + j - 1;
			return (0);
		}
		else
			j = 0;
		i++;
	}
	*index = 1;
	return (-1);
}

int	check_first(char *needle, char *haystak, int *start, int *index)
{
	int	i;

	i = 0;
	while (needle[i] && haystak[i] && (needle[i] == haystak[i]))
		i++;
	if (i == (int)ft_strlen(needle))
	{
		*start = i;
		return (0);
	}
	*index = 1;
	return (1);
}

int	check_glob(char *val, t_globing *node)
{
	int			val_len;
	int			ret;
	t_globing	*tmp;
	int			i;
	int			j;

	val_len = ft_strlen(val);
	tmp = node;
	ret = 1;
	i = 0;
	j = 0;
	if (node->pos == ALL)
		return (ft_strncmp(val, node->value, val_len));
	while (tmp)
	{
		if (tmp->pos == FIRST)
			ret = check_first(tmp->value, val, &i, &j);
		if (tmp->pos == MIDLLE && j == 0)
			ret = check_midd(tmp->value, val, &i, &j);
		if (tmp->pos == LAST && j == 0)
			ret = check_last(tmp->value, val, i);
		tmp = tmp->next;
	}
	return (ret);
}

int	check_node_for_valid(t_globing *wild, t_dir_cont *head, int fil_or_dir)
{
	if (fil_or_dir == DIREC && head->type != DIREC)
		return (1);
	if (wild->value == NULL && wild->pos == ALL)
		return (0);
	if (0 == check_glob(head->value, wild))
		return (0);
	(void)fil_or_dir;
	return (1);
}
