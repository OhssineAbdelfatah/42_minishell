/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:13:31 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/31 01:13:33 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_qoutes_core(t_check_quotes *var, char *s)
{
	if (s[var->i] == '"')
	{
		if (var->j == SINGLE)
			var->j = SINGLE;
		else if (var->j == DOUBLE)
			var->j = NONE;
		else
			var->j = DOUBLE;
	}
	if (s[var->i] == '\'')
	{
		if (var->j == DOUBLE)
			var->j = DOUBLE;
		else if (var->j == SINGLE)
			var->j = NONE;
		else
			var->j = SINGLE;
	}
}

int	check_qoutes(char *s)
{
	t_check_quotes	var;

	var.i = 0;
	var.j = NONE;
	if (s)
	{
		while (s[var.i])
		{
			check_qoutes_core(&var, s);
			var.i++;
		}
	}
	return (var.j);
}

int	check_ref(int i, char **tokens)
{
	int	ref;
	int	next_ref;

	ref = which_one(tokens[i]);
	next_ref = which_one(tokens[i + 1]);
	if (ref != EXEC && ref == next_ref)
	{
		if (ref != S_SUB && ref != END_SUB)
			return (ref);
	}
	if (ref == RED || ref == HERDOC)
	{
		if (next_ref != EXEC)
			return (ref);
	}
	if (ref == PIPE || ref == AND || ref == OR)
	{
		if (next_ref != EXEC && next_ref != RED && next_ref != HERDOC)
		{
			if (next_ref != S_SUB && next_ref != END_SUB)
				return (ref);
		}
	}
	return (-1);
}

int	_check_tokens_core(char **tokens, t_check_tokens *var)
{
	var->ref = which_one(tokens[var->i]);
	var->i++;
	var->next_ref = which_one(tokens[var->i]);
	if (var->ref != EXEC && var->ref == var->next_ref)
	{
		if (var->ref != S_SUB && var->ref != END_SUB)
			return (var->ref);
	}
	if (var->ref == RED || var->ref == HERDOC)
	{
		if (var->next_ref != EXEC)
			return (var->ref);
	}
	if (var->ref == PIPE || var->ref == AND || var->ref == OR)
	{
		if (var->next_ref != EXEC && var->next_ref != RED
			&& var->next_ref != HERDOC)
		{
			if (var->next_ref != S_SUB && var->next_ref != END_SUB)
				return (var->ref);
		}
	}
	return (-1);
}

int	_check_tokens(char **tokens)
{
	t_check_tokens	var;

	var.i = 0;
	var.ref = EXEC;
	if (!tokens)
		return (0);
	var.ref = which_one(tokens[var.i]);
	if (var.ref == AND || var.ref == PIPE || var.ref == OR)
		return (var.ref);
	if (check_tok_sub(tokens))
		return (1008);
	while (tokens[var.i])
	{
		var.tmp = _check_tokens_core(tokens, &var);
		if (var.tmp != -1)
			return (var.tmp);
	}
	if (var.ref == END_SUB)
		var.ref = SUB_SH;
	return (var.ref);
}
