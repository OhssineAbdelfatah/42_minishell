/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:49:43 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/30 14:49:44 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_there_cmd_after(char **tokens, int i)
{
	int	ref;
	int	prev_ref;

	i++;
	if (tokens[i] && which_one(tokens[i]) == S_SUB)
		return (1);
	while (tokens[i])
	{
		ref = which_one(tokens[i]);
		if (ref == AND || ref == OR || ref == PIPE || ref == END_SUB)
			break ;
		if (ref == EXEC)
		{
			if (prev_ref == HERDOC || prev_ref == RED)
				ref = FILE_NAME;
			else
				return (1);
		}
		i++;
		prev_ref = ref;
	}
	return (0);
}

int	is_there_cmd_before(char **tokens, int i)
{
	int	ref;

	if (i == 0)
		return (1);
	i--;
	ref = which_one(tokens[i]);
	if (ref == AND || ref == OR || ref == PIPE || ref == S_SUB)
		return (1);
	if (ref == HERDOC || ref == RED)
		return (1);
	if (ref == EXEC || ref == END_SUB)
		return (0);
	return (0);
}

int	handel_s_sub(char **tokens, t_check_sub_tok *var)
{
	if (var->i > 0 && which_one(tokens[var->i - 1]) == EXEC)
		return (error(NULL, 40), 7878);
	if (tokens[var->i + 1])
	{
		var->which = which_one(tokens[var->i + 1]);
		if (var->which != EXEC && var->which != S_SUB && var->which != HERDOC
			&& var->which != RED)
			return (error(NULL, 41), 1008);
	}
	return (0);
}

int	check_tok_sub(char **tokens)
{
	t_check_sub_tok	var;

	var.i = 0;
	while (tokens[var.i])
	{
		var.ref = which_one(tokens[var.i]);
		if (var.ref == S_SUB)
		{
			var.ret = handel_s_sub(tokens, &var);
			if (var.ret)
				return (var.ret);
		}
		if (var.ref == END_SUB)
		{
			if (is_there_cmd_after(tokens, var.i))
				return (error(NULL, 41), 1008);
			if (is_there_cmd_before(tokens, var.i))
				return (error(NULL, 41), 1008);
		}
		var.i++;
	}
	return (0);
}
