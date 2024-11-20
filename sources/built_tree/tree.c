/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:10:13 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/06 10:08:08 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PARSE NEW_EXEC
/******************************************** */

t_cmd	*parse_new_exec(char **tokens, int *i, t_env **env)
{
	t_parse_new_exec	var;

	var.res = NULL;
	var.x = *i;
	var.herdoc = (t_herdoc *)malloc(sizeof(*var.herdoc));
	if (!var.herdoc)
		panic("malloc failed\n");
	var.herdoc->herdoc_pipe = -1;
	var.herdoc->to_exp = 0;
	get_herdoc(tokens, var.x, var.herdoc);
	var.argv = cmd_line(tokens, i);
	var.argv1 = fr9_trb7(var.argv);
	free(var.argv);
	var.redirect = get_red(tokens, var.x, var.herdoc);
	var.res = (t_cmd *)init_new_cmd(var.argv1, env, var.redirect, var.herdoc);
	return (var.res);
}

/***************************************************************** */
// PARSE_SUB
/*********************************************************** */

t_cmd	*parse_sub(char **tokens, int *i, t_env **myenv)
{
	t_parse_sub	var;

	var.res = NULL;
	var.x = *i;
	var.herdoc = (t_herdoc *)malloc(sizeof(*var.herdoc));
	if (!var.herdoc)
		panic("malloc failed\n");
	var.end_sub = get_end_sub(tokens, *i);
	var.herdoc->herdoc_pipe = -1;
	var.herdoc->to_exp = 0;
	get_herdoc(tokens, *i, var.herdoc);
	(*i)++;
	var.sub_root = parse_and_or(tokens, i, myenv);
	var.redirect = get_red_for_sub(tokens, var.x);
	*i = var.end_sub;
	var.res = (t_cmd *)init_sub(var.sub_root, myenv, var.redirect, var.herdoc);
	return (var.res);
}

/*********************************************************** */
// PARSE PIPE WITH RECURSION :
/********************************************************* */

t_cmd	*parse_pipe_rec(char **tokens, int *i, t_env **myenv)
{
	t_cmd	*res;
	int		what_next;

	what_next = which_one(tokens[*i]);
	if (tokens[*i] && what_next == S_SUB)
		res = parse_sub(tokens, i, myenv);
	else if (tokens[*i] && (what_next == EXEC || what_next == HERDOC
			|| what_next == RED))
		res = parse_new_exec(tokens, i, myenv);
	if (tokens[*i] && is_pipe(tokens[*i]))
	{
		(*i)++;
		res = (t_cmd *)init_pipe(res, parse_pipe_rec(tokens, i, myenv));
	}
	return (res);
}

/************************************************************************* */
// PARSE AND | OR
/************************************************************************* */

t_cmd	*parse_and_or(char **tokens, int *i, t_env **myenv)
{
	t_cmd	*res;
	int		ref;

	res = parse_pipe_rec(tokens, i, myenv);
	ref = is_and_or(tokens[*i]);
	while (tokens[*i] && ref != -1)
	{
		if (ref == AND)
		{
			(*i)++;
			res = (t_cmd *)init_and(res, parse_pipe_rec(tokens, i, myenv));
		}
		if (ref == OR)
		{
			(*i)++;
			res = (t_cmd *)init_or(res, parse_pipe_rec(tokens, i, myenv));
		}
		ref = is_and_or(tokens[*i]);
	}
	return (res);
}

/*************************************************************************** */

t_cmd	*root(char **tokens, t_env **env)
{
	int		i;
	t_cmd	*res;

	i = 0;
	res = NULL;
	res = parse_and_or(tokens, &i, env);
	return (res);
}
