/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:25:00 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/02 06:40:46 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quoted(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == '\'' || s[i] == '"')
				return (1);
			i++;
		}
	}
	return (0);
}

int	next_nonspecial(char *s, int i)
{
	while (s[i] && 0 <= is_special(s[i]))
		i++;
	return (i);
}
