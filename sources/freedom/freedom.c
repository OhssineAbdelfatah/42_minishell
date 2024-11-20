/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:59:54 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 18:59:55 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_new_cmd(t_cmd *cmd)
{
	t_cmd_exec	*p;

	p = (t_cmd_exec *)cmd;
	free_mynigga(p->argv);
	if (NULL != p->redirect)
		free_red_lst(&(p->redirect));
	if (NULL != p->herdoc)
	{
		if (p->herdoc->herdoc_pipe != -1)
			close(p->herdoc->herdoc_pipe);
		p->herdoc->herdoc_pipe = -1;
		free(p->herdoc);
	}
	p->herdoc = NULL;
	free(p);
}

void	free_sub(t_sub_sh *cmd)
{
	if (NULL != cmd->redirect)
		free_red_lst(&(cmd->redirect));
	if (NULL != cmd->herdoc)
	{
		if (cmd->herdoc->herdoc_pipe != -1)
			close(cmd->herdoc->herdoc_pipe);
		cmd->herdoc->herdoc_pipe = -1;
		free(cmd->herdoc);
	}
	cmd->herdoc = NULL;
	free(cmd);
}

void	free_pipe2(t_cmd *cmd)
{
	t_pipe	*p;

	p = (t_pipe *)cmd;
	free_tree2((p->left));
	free_tree2((p->right));
	free(p);
	p = NULL;
}

void	free_or(t_cmd *cmd)
{
	t_or	*p;

	p = (t_or *)cmd;
	free_tree2((p->left));
	free_tree2((p->right));
	free(p);
	p = NULL;
}

void	free_and(t_cmd *cmd)
{
	t_and	*p;

	p = (t_and *)cmd;
	free_tree2((p->left));
	free_tree2((p->right));
	free(p);
	p = NULL;
}
