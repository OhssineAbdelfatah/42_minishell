/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:24 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/30 15:08:26 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	count_words_core(char *s, t_count_words *var)
{
	if (s[var->i] == '"' || s[var->i] == '\'')
	{
		var->i = get_next_quote(s, var->i);
		if (var->ref != STRING)
			var->res++;
		var->ref = STRING;
	}
	if (0 == is_white(s[var->i]))
		var->ref = SPACES;
	if (0 <= is_special(s[var->i]))
		var->ref = SPECIAL;
	if ((s[var->i] != '"' || s[var->i] != '\'') && (is_white(s[var->i])))
	{
		if (-1 == is_special(s[var->i]))
		{
			if (var->ref != STRING)
			{
				var->ref = STRING;
				var->res++;
			}
		}
	}
}

int	count_words(char *s)
{
	t_count_words	var;

	var.i = 0;
	var.res = 0;
	if (!s)
		return (0);
	var.ref = NOTHING;
	while (s[var.i])
	{
		count_words_core(s, &var);
		var.i++;
	}
	return (var.res);
}

int	get_next_parenties_d(char **s, int i)
{
	int	ref;

	ref = 0;
	while (s[i])
	{
		if (which_one(s[i]) == END_SUB && ref == 0)
			return (i);
		else if (which_one(s[i]) == END_SUB && ref != 0)
			ref--;
		i++;
		if (which_one(s[i]) == S_SUB)
			ref++;
	}
	error(NULL, 40);
	return (-1);
}

int	get_tok_len(char *s)
{
	int	pipe_red;
	int	and_or;
	int	words;
	int	sub_sh;
	int	res;

	if (!s)
		return (0);
	and_or = counts_and_or(s);
	pipe_red = count_pipe_red(s);
	words = count_words(s);
	sub_sh = count_sub_sh(s);
	if (sub_sh < 0)
		return (-1);
	res = words + and_or + pipe_red + sub_sh;
	return (res);
}

char	**fr9_trb7(char *s)
{
	t_tfar9	var;

	if (NULL == s)
		return (NULL);
	var.reslen = get_tok_len(s);
	if (var.reslen <= 0)
		return (NULL);
	var.res = (char **)malloc(sizeof(char *) * (var.reslen + 1));
	if (NULL == var.res)
		return (NULL);
	var.i = 0;
	var.end = 0;
	while (var.i < var.reslen)
	{
		var.start = get_starto(s, var.end);
		var.end = get_endo(s, var.start);
		var.res[var.i] = ft_substr(s, var.start, var.end - var.start);
		if (NULL == (var.res[var.i]))
			panic("malloc failed !\n");
		var.i++;
	}
	var.res[var.i] = NULL;
	return (var.res);
}

// int	las_part_pro(char *s, t_ct_tk_pro *var)
// {
// 	if (s[var->i] && is_white(s[var->i]) && (0 == is_special(s[var->i]))
// 		&& s[var->i] != '\'' && s[var->i] != '"')
// 	{
// 		if (var->ref == RED)
// 			var->ref = FILE_NAME;
// 		else
// 			var->ref = EXEC;
// 		var->res++;
// 		while (s[var->i] && is_white(s[var->i]) && (0 == is_special(s[var->i]))
// 			&& s[var->i] != '\'' && s[var->i] != '"')
// 		{
// 			var->i++;
// 			if (s[var->i] == '\'' || s[var->i] == '"')
// 			{
// 				while (s[var->i] && (s[var->i] == '\'' || s[var->i] == '"'))
// 					var->i = get_next_quote(s, var->i) + 1;
// 			}
// 		}
// 	}
// 	if (0 == s[var->i] && RED == var->ref)
// 		return (-2);
// 	if (0 == s[var->i] && PIPE == var->ref)
// 		return (-1);
// 	return (0);
// }

// void	middle_game(char *s, t_ct_tk_pro *var)
// {
// 	if (s[var->i] == '\'' || s[var->i] == '"')
// 	{
// 		var->ref = STRING;
// 		var->res++;
// 		while (s[var->i] && (s[var->i] == '\'' || s[var->i] == '"'))
// 		{
// 			var->i = get_next_quote(s, var->i) + 1;
// 			while (s[var->i] && is_white(s[var->i])
// 				&& (0 == is_special(s[var->i])) && s[var->i] != '\''
// 				&& s[var->i] != '"')
// 				var->i++;
// 		}
// 	}
// }

// int	count_tokens_pro(char *s)
// {
// 	t_ct_tk_pro	var;

// 	if (NULL == s)
// 		return (0);
// 	var.res = 0;
// 	var.i = 0;
// 	var.ref = NOTHING;
// 	while (s[var.i])
// 	{
// 		var.i = skip_spaces(s, var.i);
// 		var.tmp = red_or_pipe_check(s, &var);
// 		if (var.tmp < 0)
// 			return (var.ref);
// 		var.i = skip_spaces(s, var.i);
// 		middle_game(s, &var);
// 		var.i = skip_spaces(s, var.i);
// 		var.tmp = las_part_pro(s, &var);
// 		if (0 != var.tmp)
// 			return (var.tmp);
// 	}
// 	return (var.res);
// }

// int	red_or_pipe_check(char *s, t_ct_tk_pro *var)
// {
// 	if (s[var->i] == '|')
// 	{
// 		if (s[var->i + 1] == '|')
// 			var->ref = AND;
// 		if (var->ref == NOTHING || var->ref == PIPE || var->ref == RED)
// 			return (-1);
// 		var->ref = PIPE;
// 		var->res++;
// 		var->i++;
// 	}
// 	if (RED == red_or_pipe(s[var->i]))
// 	{
// 		if (RED == var->ref)
// 			return (-2);
// 		var->ref = RED;
// 		var->res++;
// 		while (s[var->i] && (RED == red_or_pipe(s[var->i])))
// 			var->i++;
// 	}
// 	return (0);
// }