/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:29:20 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/31 01:29:21 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	red_or_pipe(char c)
{
	if (0 == c)
		return (-1);
	if (c == '|')
		return (PIPE);
	if (c == '>' || c == '<')
		return (RED);
	return (-2);
}

int	get_starto(char *s, int x)
{
	if (s[x] == 0)
		return (x);
	if (0 == is_white(s[x]))
		return (skip_spaces(s, x));
	if (0 == x)
		return (x);
	return (x);
}

void	get_endo_child(char *s, int *x)
{
	if (s[*x] == '\'' || s[*x] == '"')
	{
		while (-1 == is_special(s[*x]) && is_white(s[*x]) && (s[*x] == '\''
				|| s[*x] == '"'))
			*x = get_next_quote(s, *x) + 1;
	}
	while (s[*x] && (-1 == is_special(s[*x])) && is_white(s[*x]))
	{
		if (s[*x] == '\'' || s[*x] == '"')
		{
			while (s[*x] && (s[*x] == '\'' || s[*x] == '"'))
				*x = get_next_quote(s, *x) + 1;
		}
		else
			(*x)++;
	}
}

int	get_endo(char *s, int x)
{
	int	j;

	if (s[x] == 0)
		return (x);
	if (0 <= is_special(s[x]))
	{
		if (s[x] == 40 || s[x] == 41)
			return (x + 1);
		j = is_special(s[x]);
		while (s[x] && j == is_special(s[x]))
			x++;
		return (x);
	}
	if (-1 == is_special(s[x]) && is_white(s[x]))
		get_endo_child(s, &x);
	return (x);
}
