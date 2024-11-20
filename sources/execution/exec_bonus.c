/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:12 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:19:47 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_sub_sh_core(t_exec_sub_sh *var, int *last_status)
{
	signal(SIGQUIT, NULL);
	var->std[0] = &(var->p->fd_in);
	var->std[1] = &(var->p->fd_out);
	var->std[2] = &(var->sub_status);
	var->std[3] = last_status;
	if (var->p->redirect)
		if (exec_red(var->p->redirect, var->std, var->p->herdoc,
				*(var->p->myenv)) == 1)
			exit(1);
	if (var->p->fd_in != -1 || var->p->fd_out != -1)
	{
		if (var->p->fd_out != -1)
		{
			dup2(var->p->fd_out, 1);
			close(var->p->fd_out);
		}
		if (var->p->fd_in != -1)
		{
			dup2(var->p->fd_in, 0);
			close(var->p->fd_in);
		}
	}
	var->sub_status = new_exec(var->p->sub_root, last_status);
	exit(var->sub_status);
}

int	exec_sub_sh(t_cmd *cmd, int *last_status)
{
	t_exec_sub_sh	var;

	var.p = (t_sub_sh *)cmd;
	var.pid = fork();
	var.sub_status = 0;
	if (var.pid == 0)
		exec_sub_sh_core(&var, last_status);
	signal(SIGQUIT, do_nothing);
	signal(SIGINT, SIG_IGN);
	waitpid(var.pid, &(var.sub_status), 0);
	*last_status = WEXITSTATUS(var.sub_status);
	return (*last_status);
}
