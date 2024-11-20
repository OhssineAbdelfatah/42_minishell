/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:15 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:21:02 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_simple_cmd(t_cmd_exec *p)
{
	char	**cur_env;
	char	*abs_path;

	cur_env = lstoarry(*(p->myenv));
	abs_path = NULL;
	handle_error(p, &abs_path);
	if (dstr_len(p->argv))
	{
		if (-1 == execve(abs_path, p->argv, cur_env))
			error_exec_new(p->argv[0], 127);
	}
	free(abs_path);
	return (0);
}

int	exec_new_cmd(t_cmd *cmd, int *last_status)
{
	t_cmd_exec	*p;
	int			status;
	int			ref;
	char		**tmp_clone;

	ref = NOT_SIMPLE;
	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	p = (t_cmd_exec *)cmd;
	status = 0;
	tmp_clone = clone(p->argv, dstr_len(p->argv));
	p->argv = expander(p->argv, *(p->myenv), last_status, CMD_EXPN);
	p->argv = check_empty_ones(p->argv, tmp_clone);
	p->argv = wild_expand(p->argv);
	status = check_red(p, &ref, last_status);
	if (status == 1)
		return (status);
	if (!(p->argv) || !(*(p->argv)))
		exit(status);
	if (is_builtin(cmd, &status, last_status, NOT_SIMPLE))
		exit(status);
	else
		exec_simple_cmd(p);
	free_mynigga(p->argv);
	return (status);
}

void	__sig_exec_one(int pid, int *status)
{
	signal(SIGQUIT, do_nothing);
	signal(SIGINT, do_nothing);
	waitpid(pid, status, 0);
	if (WTERMSIG(*status) == SIGINT)
		*status = 130;
	if (WTERMSIG(*status) == SIGQUIT)
		*status = 131;
	else
		*status = WEXITSTATUS(*status);
	return ;
}

int	new_exec1(t_cmd *cmd, int *last_status)
{
	int			status;
	int			pid;
	t_cmd_exec	*p;

	status = 0;
	p = (t_cmd_exec *)cmd;
	if (!p)
		return (0);
	if (is_builtin(cmd, &status, last_status, SIMPLE))
		reset_fds(cmd);
	else
	{
		pid = fork();
		if (pid == 0)
			exec_new_cmd(cmd, last_status);
		else
			__sig_exec_one(pid, &status);
	}
	return (status);
}

int	new_exec(t_cmd *cmd, int *last_status)
{
	int	status;

	status = 0;
	if (NEW_CMD == cmd->type)
		status = new_exec1(cmd, last_status);
	else if (AND == cmd->type)
		status = exec_and(cmd, last_status);
	else if (OR == cmd->type)
		status = exec_or(cmd, last_status);
	else if (SUB_SH == cmd->type)
		status = exec_sub_sh(cmd, last_status);
	else if (PIPE == cmd->type)
	{
		status = exec_pipe(cmd, last_status);
		if (status != 130 && status != 131)
			status = WEXITSTATUS(status);
	}
	return (status);
}
