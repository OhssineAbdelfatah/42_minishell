/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:53:13 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:53:15 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	freeglobing(t_globing **head)
{
	t_globing	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->value);
		free(*head);
		*head = tmp;
	}
}

t_globing	*create_glob_node(char *value, int pos)
{
	t_globing	*node;

	node = (t_globing *)malloc(sizeof(t_globing));
	if (!node)
		panic("malloc failed !");
	if (is_quoted(value))
		value = whithout_quotes(value, 1);
	node->value = value;
	node->pos = pos;
	node->found_it = 0;
	node->next = NULL;
	return (node);
}

t_globing	*add_glob_node(t_globing *head, t_globing *new)
{
	t_globing	*tmp;

	if (!head)
		return (new);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

void	wilding_ww(t_wild *var, char *s)
{
	var->j = get_next_wild(s, var->i);
	var->val = ft_substr(s, var->i, var->j - var->i);
	if (var->i == 0)
	{
		var->pos = FIRST;
		if (var->j == var->slen)
			var->pos = ALL;
	}
	else if (var->j == var->slen)
		var->pos = LAST;
	else
		var->pos = MIDLLE;
	var->ret = add_glob_node(var->ret, create_glob_node(var->val, var->pos));
	var->i = var->j;
}

t_globing	*wilding(char *s)
{
	t_wild	var;

	var.i = 0;
	var.j = 0;
	var.ret = NULL;
	var.slen = (int)ft_strlen(s);
	while (s[var.i])
	{
		if (s[var.i] != '*')
			wilding_ww(&var, s);
		if (s[var.i])
			var.i++;
	}
	if (!var.ret)
		var.ret = create_glob_node(NULL, ALL);
	return (var.ret);
}

// var.j = get_next_wild(s, var.i);
// var.val = ft_substr(s, var.i, var.j - var.i);
// if (var.i == 0)
// {
// 	var.pos = FIRST;
// 	if (var.j == var.slen)
// 		var.pos = ALL;
// }
// else if (var.j == var.slen)
// 	var.pos = LAST;
// else
// 	var.pos = MIDLLE;
// var.ret = add_glob_node(var.ret, create_glob_node(var.val,
// 			var.pos));
// var.i = var.j;
//
// void	print_glob(t_globing *head)
// {
// 	t_globing	*tmp;
//
// 	tmp = head;
// 	while (tmp)
// 	{
// 		printf("val : %s, Pose: %d\n", tmp->value, tmp->pos);
// 		tmp = tmp->next;
// 	}
// }