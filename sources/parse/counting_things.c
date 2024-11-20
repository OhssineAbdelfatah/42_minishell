/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_things.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:06:31 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/30 15:06:33 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	counts_and_or(char *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i = get_next_quote(s, i);
		if (s[i] == '|' && s[i + 1] == '|')
			res++;
		if (s[i] == '&' && s[i + 1] == '&')
			res++;
		i++;
	}
	return (res);
}

int	count_red(char *s, t_count_pipe_red *var)
{
	if (s[var->i] == '>')
	{
		if (s[var->i + 1] == '>')
			var->i++;
		var->res++;
	}
	if (s[var->i] == '<')
	{
		if (s[var->i + 1] == '<')
			var->i++;
		var->res++;
	}
	return (0);
}

int	count_pipe_red(char *s)
{
	t_count_pipe_red	var;

	var.i = 0;
	var.res = 0;
	while (s[var.i])
	{
		if (s[var.i] == '\'' || s[var.i] == '"')
			var.i = get_next_quote(s, var.i);
		if (s[var.i + 1] != '|' && s[var.i] == '|')
		{
			var.res++;
			if (var.i > 0 && s[var.i - 1] == '|')
				var.res--;
		}
		if (s[var.i] == '<' || s[var.i] == '>')
			count_red(s, &var);
		var.i++;
	}
	return (var.res);
}

int	count_sub_sh(char *s)
{
	t_count_sub_sh	var;

	var.res = 0;
	var.i = 0;
	var.next_par = 0;
	while (s[var.i])
	{
		if (s[var.i] == '"' || s[var.i] == '\'')
			var.i = get_next_quote(s, var.i);
		if (s[var.i] == ')' && var.res == 0)
			return (error(NULL, 41), -1);
		if (s[var.i] == '(')
		{
			var.next_par = get_next_parenties(s, var.i);
			if (var.next_par < 0)
				return (-1);
			else
				var.res += 2;
		}
		var.i++;
	}
	if (var.res != total_sub(s))
		return (error(NULL, 41), -1);
	return (var.res);
}

// int	count_pipe_red(char *s)
// {
// 	int i;
// 	int res;

// 	i = 0;
// 	res = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' || s[i] == '"')
// 			i = get_next_quote(s, i);
// 		if (s[i + 1] != '|' && s[i] == '|')
// 		{
// 			res++;
// 			if (i > 0 && s[i - 1] == '|')
// 				res--;
// 		}
// 		if (s[i] == '>')
// 		{
// 			if (s[i + 1] == '>')
// 				i++;
// 			res++;
// 		}
// 		if (s[i] == '<')
// 		{
// 			if (s[i + 1] == '<')
// 				i++;
// 			res++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }
