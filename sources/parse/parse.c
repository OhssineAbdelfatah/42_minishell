/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:58:35 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 19:58:36 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_start(char *s, int i)
{
	if (s)
	{
		if (s[i] == 32 || (s[i] <= 13 && s[i] >= 9))
			return (skip_spaces(s, i));
		else
			return (i);
	}
	return (i);
}

int	get_end(char *s, int i)
{
	if (s[i] == '|')
		return (i + 1);
	if (is_special(s[i]))
		return (next_nonspecial(s, i));
	else
	{
		while (s[i] && !is_special(s[i]))
		{
			if (s[i] == '\'' || s[i] == '"')
				i = get_next_quote(s, i);
			i++;
			if (is_special(s[i]) && is_white(s[i - 1]))
			{
				i--;
				while (i > 0 && (s[i] == 32 || (s[i] <= 13 && s[i] >= 9)))
					i--;
				i++;
				return (i);
			}
		}
	}
	return (i);
}

int	check_dtr_for_and(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '"' || s[i] == '\'')
		i = get_next_quote(s, i);
	if (s[i] == '&' && s[i + 1] != '&')
		return (1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(s, i);
		if (i > 0)
		{
			if (s[i] == '&' && s[i + 1] != '&' && s[i - 1] != '&')
				return (1);
		}
		if (s[i])
			i++;
	}
	return (0);
}

int	_check_str_core(char *s, int i)
{
	if (s[i] == '|' && s[i + 1] == '|' && s[i + 2] == '|')
		return (error(s, PIPE), 1);
	if (s[i] == '&' && s[i + 1] == '&' && s[i + 2] == '&')
		return (error(s, AND), 1);
	if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<')
		return (error(s, RED), 1);
	if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>')
		return (error(s, RED), 1);
	return (0);
}

int	_check_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	if (check_qoutes(s))
		return (error(s, 10), 1);
	if (is_full_white_str(s))
		return (1);
	if (check_dtr_for_and(s))
		return (error(s, AND), 1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(s, i);
		if (_check_str_core(s, i))
			return (1);
		else if (s[i])
			i++;
	}
	return (0);
}
