/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:49 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 14:01:50 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_reslen(char *s)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			j = i;
			i = get_next_quote(s, i);
			res = res + (i - (j + 1));
		}
		else
			res++;
		i++;
	}
	return (res);
}

void	init_vars(t_without_quotes *var, char *value)
{
	var->i = 0;
	var->j = 0;
	var->end = -1;
	var->res_len = get_reslen(value);
	var->res = (char *)malloc(var->res_len + 1);
	if (!var->res)
		panic("malloc failed !\n");
}

char	*whithout_quotes(char *value, int to_free)
{
	t_without_quotes	var;

	init_vars(&var, value);
	while (var.i < var.res_len)
	{
		if (var.end == -1 && (value[var.j] == '\'' || value[var.j] == '"'))
		{
			var.end = get_next_quote(value, var.j);
			var.j++;
		}
		if (var.j != var.end)
			var.res[var.i++] = value[var.j++];
		if (var.j == var.end)
		{
			var.end = -1;
			var.j++;
		}
	}
	var.res[var.i] = 0;
	if (to_free)
		free(value);
	return (var.res);
}

t_del	*first_del(t_del *node, char *value)
{
	t_del	*res;

	res = NULL;
	if (NULL == node)
	{
		res = (t_del *)malloc(sizeof(t_del));
		if (!res)
			return (NULL);
		res->to_exp = 0;
		if (is_quoted(value))
		{
			res->to_exp = 1;
			res->del = whithout_quotes(value, 1);
		}
		else
			res->del = value;
		res->next = NULL;
	}
	return (res);
}

t_del	*add(t_del *node, char *value)
{
	t_del	*res;
	t_del	*tmp;

	tmp = node;
	if (NULL == node)
		return (first_del(node, value));
	while (tmp->next)
		tmp = tmp->next;
	res = (t_del *)malloc(sizeof(t_del));
	if (is_quoted(value))
	{
		res->to_exp = 1;
		res->del = whithout_quotes(value, 1);
	}
	else
		res->del = value;
	res->next = NULL;
	tmp->next = res;
	return (node);
}

// void	print_del(t_del *head)
// {
// 	t_del	*tmp;

// 	tmp = head;
// 	if (head == NULL)
// 	{
// 		printf("empty \n");
// 		return ;
// 	}
// 	while (tmp != NULL)
// 	{
// 		printf("del:%s\n", tmp->del);
// 		printf("to_exp:%d\n", tmp->to_exp);
// 		tmp = tmp->next;
// 	}
// }
// int	to_exp_doc(t_del *head)
// {
// 	t_del	*tmp;

// 	tmp = head;
// 	if (tmp == NULL)
// 		return (0);
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	return (0);
// }
