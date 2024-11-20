/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:02:10 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 20:02:11 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_next_quote(char *s, int i)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
	}
	else
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	return (i);
}

int	which_one(char *s)
{
	if (!s)
		return (-1);
	if (ft_strlen(s) == 1 && s[0] == '|')
		return (PIPE);
	if (ft_strlen(s) == 1 && s[0] == 40)
		return (S_SUB);
	if (ft_strlen(s) == 1 && s[0] == 41)
		return (END_SUB);
	if (ft_strlen(s) == 2)
	{
		if (ft_strcmp(s, "<<"))
			return (HERDOC);
		if (ft_strcmp(s, ">>"))
			return (RED);
		if (ft_strcmp(s, "&&"))
			return (AND);
		if (ft_strcmp(s, "||"))
			return (OR);
	}
	if (s[1] == '\0' && (s[0] == '>' || s[0] == '<'))
		return (RED);
	return (EXEC);
}

int	is_special(char s)
{
	int		i;
	char	*symbols;

	symbols = "|<>&()";
	i = 0;
	if (s)
	{
		while (symbols[i])
		{
			if (symbols[i] == s)
				return (i);
			i++;
		}
	}
	return (-1);
}
