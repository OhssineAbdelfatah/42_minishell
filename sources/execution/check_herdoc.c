/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:09 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/11 02:06:22 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	last_herdoc(t_red *lst)
{
	t_red	*tmp;

	if (lst)
	{
		tmp = lst->next;
		while (tmp)
		{
			if (tmp->type == HERDOC)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

void	open_herdoc(t_red *redirect, int *std[4], t_herdoc *herdoc, t_env *env)
{
	if (*std[0] != -1 && last_herdoc(redirect))
		close(*std[0]);
	if (last_herdoc(redirect))
	{
		*std[0] = herdoc->herdoc_pipe;
		if (!herdoc->to_exp)
			*std[0] = herdoc_newfd(herdoc->herdoc_pipe, env, std[3]);
	}
}

int	exec_red(t_red *redirect, int *std[4], t_herdoc *herdoc, t_env *env)
{
	int		status;
	t_red	*tmp;

	status = 0;
	tmp = redirect->next;
	while (redirect)
	{
		tmp = redirect->next;
		status = open_file(redirect, std, herdoc, env);
		if (status)
			return (status);
		redirect = tmp;
	}
	return (status);
}

void	set_stds(int *std[4], int *ref, int *last_status, t_cmd_exec *p)
{
	std[0] = &(p->fd_in);
	std[1] = &(p->fd_out);
	std[2] = ref;
	std[3] = last_status;
}

int	check_red(t_cmd_exec *p, int *ref, int *last_status)
{
	int	status;
	int	*std[4];

	status = 0;
	set_stds(std, ref, last_status, p);
	if (NULL != p->redirect)
		status = exec_red(p->redirect, std, p->herdoc, *(p->myenv));
	if (status)
		return (status);
	if (p->fd_in != -1 || p->fd_out != -1)
	{
		if (p->fd_out != -1)
		{
			p->std_out = dup(1);
			dup2(*std[1], 1);
			close(*std[1]);
		}
		if (p->fd_in != -1)
		{
			p->std_in = dup(0);
			dup2(*std[0], 0);
			close(*std[0]);
		}
	}
	return (status);
}
