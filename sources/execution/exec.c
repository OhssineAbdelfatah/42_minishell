/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:20 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:20:18 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmd_type(t_cmd *cmd)
{
	if (cmd->type == NEW_CMD)
		return (1);
	return (0);
}

int	dstr_len(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

int	exec_and(t_cmd *cmd, int *last_status)
{
	t_and	*and_cmd;
	int		status;

	and_cmd = (t_and *)cmd;
	status = new_exec(and_cmd->left, last_status);
	if (status == 0)
		status = new_exec(and_cmd->right, last_status);
	return (status);
}

int	exec_or(t_cmd *cmd, int *last_status)
{
	t_or	*or_cmd;
	int		status;

	or_cmd = (t_or *)cmd;
	status = new_exec(or_cmd->left, last_status);
	if (status != 0)
		status = new_exec(or_cmd->right, last_status);
	return (status);
}
