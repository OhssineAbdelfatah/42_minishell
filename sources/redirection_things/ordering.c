/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:28:00 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 20:28:02 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_cmd(char *s1, char *s2)
{
	int		i;
	int		reslen;
	char	*res;
	int		l;

	reslen = ft_strlen(s1) + ft_strlen(s2);
	if (NULL != s1)
		reslen += 1;
	res = (char *)malloc(reslen + 1);
	l = ft_strlen(s1);
	i = 0;
	while (i < l)
	{
		res[i] = s1[i];
		i++;
	}
	if (l > 0)
		res[i] = 32;
	i++;
	l = 0;
	while ((size_t)l < ft_strlen(s2))
		res[i++] = s2[l++];
	res[i] = 0;
	free(s1);
	return (res);
}

int	while_breaker(t_cmd_line *var, char **tokens)
{
	if (PIPE == var->j || var->j == OR || var->j == AND || var->j == END_SUB
		|| var->j == S_SUB)
		return (1);
	if (var->ref == RED || var->ref == HERDOC)
		var->ref = FILE_NAME;
	else if (FILE_NAME == var->ref)
		var->ref = EXEC;
	if (var->j == RED || var->j == HERDOC)
		var->ref = var->j;
	if (var->ref == EXEC)
	{
		if (NULL == var->cmd)
			var->cmd = ft_strdup(tokens[var->i]);
		else
			var->cmd = join_cmd(var->cmd, tokens[var->i]);
	}
	return (0);
}

char	*cmd_line(char **tokens, int *x)
{
	t_cmd_line	var;

	var.i = *x;
	var.ref = EXEC;
	var.cmd = NULL;
	while (tokens[var.i])
	{
		var.j = which_one(tokens[var.i]);
		if (while_breaker(&var, tokens))
			break ;
		var.i++;
	}
	*x = var.i;
	return (var.cmd);
}

t_red	*get_red(char **tokens, int i, t_herdoc *herdoc)
{
	t_red	*red_lst;
	int		ref;

	red_lst = NULL;
	ref = which_one(tokens[i]);
	(void)herdoc;
	while (tokens[i] && PIPE != ref && ref != AND && ref != OR)
	{
		if (ref == END_SUB)
			break ;
		ref = which_one(tokens[i]);
		if (ref == RED || HERDOC == ref)
		{
			if (NULL == red_lst)
				red_lst = creat_red_lst(tokens, i);
			else
				add_to_lst(red_lst, tokens, i);
			if (!red_lst)
				return (NULL);
			i++;
		}
		i++;
	}
	return (red_lst);
}

t_red	*get_red_for_sub(char **tokens, int i)
{
	t_red	*red_lst;
	int		ref;

	red_lst = NULL;
	ref = 0;
	i = get_next_parenties_d(tokens, i) + 1;
	while (tokens[i] && PIPE != ref && ref != AND && ref != OR)
	{
		ref = which_one(tokens[i]);
		if (ref == END_SUB)
			break ;
		if (ref == RED || HERDOC == ref)
		{
			if (NULL == red_lst)
				red_lst = creat_red_lst(tokens, i);
			else
				add_to_lst(red_lst, tokens, i);
			if (!red_lst)
				return (NULL);
			i++;
		}
		i++;
	}
	return (red_lst);
}
