/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:48:54 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/30 14:48:55 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_work(t_herdoc_treat *var, t_del *lst)
{
	signal(SIGINT, NULL);
	while (lst != NULL)
	{
		while (1)
		{
			var->str = readline(">");
			if (!var->str)
				break ;
			if (ft_strcmp(var->str, lst->del))
			{
				free(var->str);
				break ;
			}
			if (lst->next == NULL)
			{
				ft_putstr_fd(var->str, var->p[1]);
				ft_putstr_fd("\n", var->p[1]);
			}
			free(var->str);
		}
		lst = lst->next;
	}
	close(var->p[1]);
	close(var->p[0]);
	exit(0);
}

void	parent_work(t_herdoc_treat *var, t_herdoc *herdoc)
{
	signal(SIGINT, do_nothing);
	waitpid(var->pid, &var->status, 0);
	if (WTERMSIG(var->status) == SIGINT)
	{
		g_sig = 131;
		var->status = 1;
	}
	else
		var->status = 0;
	if (g_sig == -1)
		herdoc->herdoc_pipe = var->p[0];
	else
		close(var->p[0]);
	close(var->p[1]);
}

int	herdoc_treat(t_del *lst, t_herdoc *herdoc)
{
	t_herdoc_treat	var;

	var.status = 0;
	if (NULL == lst)
		return (0);
	pipe(var.p);
	var.pid = fork();
	if (var.pid == 0)
		child_work(&var, lst);
	else if (var.pid > 0)
		parent_work(&var, herdoc);
	return (var.status);
}

int	while_breaker2(t_get_herdoc *var, char **tokens, int *i)
{
	if (var->ref == END_SUB || var->ref == S_SUB)
		return (1);
	var->ref = which_one(tokens[*i]);
	if (var->ref == HERDOC)
	{
		(*i)++;
		var->delimiter = ft_strdup(tokens[*i]);
		if (NULL == var->str)
			var->str = first_del(var->str, var->delimiter);
		else
			var->str = add(var->str, var->delimiter);
	}
	return (0);
}

int	get_herdoc(char **tokens, int i, t_herdoc *herdoc)
{
	t_get_herdoc	var;

	var.status = 0;
	var.str = NULL;
	var.ref = which_one(tokens[i]);
	while (tokens[i] && PIPE != var.ref && var.ref != AND && var.ref != OR)
	{
		if (while_breaker2(&var, tokens, &i))
			break ;
		i++;
	}
	assign_her_exp(var.str, herdoc);
	if (g_sig == -1)
		var.status = herdoc_treat(var.str, herdoc);
	free_delimiters(var.str);
	return (var.status);
}
