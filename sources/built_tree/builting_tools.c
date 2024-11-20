/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:15:13 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 19:15:14 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_end_sub(char **tokens, int i)
{
	int	res;
	int	ref;

	res = get_next_parenties_d(tokens, i);
	ref = which_one(tokens[res + 1]);
	if (ref == RED || ref == HERDOC)
	{
		while (ref == RED || ref == HERDOC || ref == EXEC)
		{
			ref = which_one(tokens[res + 1]);
			res++;
		}
	}
	else
		return (res + 1);
	return (res);
}

int	is_pipe(char *s)
{
	if (ft_strlen(s) == 1 && s[0] == '|')
		return (1);
	return (0);
}

int	is_and_or(char *s)
{
	if (ft_strlen(s) == 2)
	{
		if (s[0] == '&' && s[1] == '&')
			return (AND);
		if (s[0] == '|' && s[0] == '|')
			return (OR);
	}
	return (-1);
}
