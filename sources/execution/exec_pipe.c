/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:49:16 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/10 23:14:18 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/******************************************************/
// THE MIGHTY PERFECT EXEC PIPE FUNCTION !!
/**********************************************************/

void	treat_left_child(t_cmd *left_cmd, t_execp *sp, int *last_status)
{
	t_cmd_exec	*left_one;

	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	if (left_cmd->type == NEW_CMD)
	{
		left_one = (t_cmd_exec *)left_cmd;
		if (sp->node_p->pipe_fd != -1)
			left_one->fd_in = sp->node_p->pipe_fd;
		left_one->fd_out = sp->p[1];
		close(sp->p[0]);
		exec_new_cmd(left_cmd, last_status);
		if (left_one->herdoc->herdoc_pipe > 0)
			close(left_one->herdoc->herdoc_pipe);
	}
	else
		left_child_is_sub(left_cmd, sp, last_status);
}

int	right_child_ispipe(t_cmd *right_cmd, t_execp *sp, int *last_status)
{
	int		status;
	t_pipe	*right_pipe;

	signal(SIGINT, SIG_IGN);
	right_pipe = (t_pipe *)right_cmd;
	right_pipe->pipe_fd = sp->p[0];
	close(sp->p[1]);
	status = exec_pipe(right_cmd, last_status);
	return (status);
}

int	treat_right_child(t_cmd *right_cmd, t_execp *sp, int *last_status)
{
	int			status;
	t_cmd_exec	*right_one;
	t_sub_sh	*right_sub;

	if (right_cmd->type == NEW_CMD)
	{
		right_one = (t_cmd_exec *)right_cmd;
		if (sp->node_p->pipe_fd != -1)
			close(sp->node_p->pipe_fd);
		right_one->fd_in = sp->p[0];
		close(sp->p[1]);
		status = exec_new_cmd(right_cmd, last_status);
		return (status);
	}
	else if (right_cmd->type == SUB_SH)
	{
		right_sub = (t_sub_sh *)right_cmd;
		if (sp->node_p->pipe_fd != -1)
			close(sp->node_p->pipe_fd);
		right_sub->fd_in = sp->p[0];
		close(sp->p[1]);
		status = exec_sub_sh(right_cmd, last_status);
		return (status);
	}
	return (0);
}

void	pipe_parent(t_execp *sp)
{
	close(sp->p[0]);
	close(sp->p[1]);
	signal(SIGQUIT, do_nothing);
	signal(SIGINT, do_nothing);
	waitpid(sp->rpid, &(sp->status), 0);
	if (WTERMSIG(sp->status) == SIGQUIT || WTERMSIG(sp->status) == SIGINT)
		sp->status = 128 + WTERMSIG(sp->status);
	wait(0);
}

int	exec_pipe(t_cmd *cmd, int *last_status)
{
	t_execp	sp;

	if (pipe(sp.p) < 0)
		return (ft_putstr_fd("minishell: pipe: Resource unavailable\n", 2), -1);
	sp.node_p = (t_pipe *)cmd;
	sp.lpid = fork();
	if (sp.lpid == 0)
		treat_left_child(sp.node_p->left, &sp, last_status);
	if (sp.node_p->right->type == PIPE)
		sp.status = right_child_ispipe(sp.node_p->right, &sp, last_status);
	else
	{
		sp.rpid = fork();
		if (sp.rpid == 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, NULL);
			sp.status = treat_right_child(sp.node_p->right, &sp, last_status);
			exit(sp.status);
		}
	}
	pipe_parent(&sp);
	return (sp.status);
}
