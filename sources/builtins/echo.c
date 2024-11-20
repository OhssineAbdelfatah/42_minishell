/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:46 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:13:40 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	isvalid_echo(char **arg)
{
	int	i;
	int	j;

	i = -1;
	while (arg[++i])
	{
		j = -1;
		if (arg[i][++j] != '-')
			break ;
		while (arg[i][++j])
		{
			if (arg[i][j] != 'n')
			{
				j = -1;
				break ;
			}
		}
		if (j == -1)
			break ;
	}
	return (i);
}

int	echo(t_new_cmd *p)
{
	int	new_line;
	int	new_line_1;

	new_line = 0;
	if (ft_strslen(p->argv) > 1 && isvalid_echo(&(p->argv[1])) > 0)
		new_line += isvalid_echo(&(p->argv[1]));
	new_line_1 = new_line;
	while (p->argv[++new_line])
	{
		ft_putstr_fd(p->argv[new_line], 1);
		if (p->argv[new_line])
			if (p->argv[new_line + 1] != NULL)
				ft_putstr_fd(" ", 1);
	}
	if (new_line_1 == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
