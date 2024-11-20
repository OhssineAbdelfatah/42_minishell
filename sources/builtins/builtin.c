/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:39 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/11 02:49:22 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_fds(t_cmd *p)
{
	t_new_cmd	*cmd;

	cmd = (t_new_cmd *)p;
	if (cmd->std_in != -1)
	{
		dup2(cmd->std_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->std_out, 1);
		close(cmd->fd_out);
	}
	return ;
}

bool	is_builtin(t_cmd *cmd, int *status, int *last_status, int ref)
{
	t_cmd_exec	*p;
	char		**bcmds;
	int			i;

	p = (t_cmd_exec *)cmd;
	if (p->argv == NULL)
		return (false);
	bcmds = ft_split("cd pwd export unset env exit echo", ' ');
	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(p->argv[0], bcmds[i]))
		{
			free_split(bcmds);
			*status = exec_builtin(cmd, last_status, ref);
			return (true);
		}
	}
	free_mynigga(bcmds);
	return (false);
}

int	exec_cmd_builtin(t_cmd_exec *p, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (ft_strcmp(p->argv[0], "cd"))
		status = cd(cmd);
	else if (ft_strcmp(p->argv[0], "pwd"))
		status = pwd();
	else if (ft_strcmp(p->argv[0], "env"))
		status = print_env(*(p->myenv));
	else if (ft_strcmp(p->argv[0], "unset"))
	{
		if (ft_strslen(p->argv) > 1)
			status = unset_env(p->myenv, p->argv);
	}
	else if (ft_strcmp(p->argv[0], "export"))
	{
		status = export(p);
	}
	else if (ft_strcmp(p->argv[0], "echo"))
		status = echo(p);
	else if (ft_strcmp(p->argv[0], "exit"))
		status = exit_blt(p);
	return (status);
}

int	exec_builtin(t_cmd *cmd, int *last_status, int ref)
{
	int			status;
	t_cmd_exec	*p;

	p = (t_cmd_exec *)cmd;
	p->argv = expander(p->argv, *(p->myenv), last_status, CMD_EXPN);
	p->argv = wild_expand(p->argv);
	if (ref == SIMPLE)
	{
		status = check_red(p, &ref, last_status);
		if (status == 1)
			return (status);
	}
	if (!p->argv || !(p->argv[0]))
		return (1);
	status = exec_cmd_builtin(p, cmd);
	return (status);
}

void	check_plus_minus(char *str, int i, int sign)
{
	if ((sign > 0 && (str[i] == '\0' || str[i] == '+')) || (sign < 0
			&& str[i] != '\0' && str[i + 1] == '-'))
	{
		my_dprint(2, "bash: exit: %s: numeric argument required\n", str - i);
		exit(255);
	}
}
