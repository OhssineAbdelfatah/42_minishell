/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constractors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:46:06 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 13:46:08 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_pipe(t_cmd *left, t_cmd *right)
{
	t_pipe	*res;

	res = malloc(sizeof(*res));
	if (!res)
		panic("init_pipe\n");
	res->type = PIPE;
	res->pipe_fd = -1;
	res->left = left;
	res->right = right;
	return ((t_cmd *)res);
}

t_cmd	*init_and(t_cmd *left, t_cmd *right)
{
	t_and	*res;

	res = malloc(sizeof(*res));
	if (!res)
		panic("init_and\n");
	res->type = AND;
	res->status = 0;
	res->left = left;
	res->right = right;
	return ((t_cmd *)res);
}

t_cmd	*init_or(t_cmd *left, t_cmd *right)
{
	t_or	*res;

	res = malloc(sizeof(*res));
	if (!res)
		panic("init_or\n");
	res->type = OR;
	res->status = 0;
	res->left = left;
	res->right = right;
	return ((t_cmd *)res);
}

t_cmd	*init_new_cmd(char **argv, t_env **myenv, t_red *redirect,
		t_herdoc *herdoc1)
{
	t_cmd_exec	*res;

	res = (t_cmd_exec *)malloc(sizeof(*res));
	if (NULL == res)
		return (NULL);
	res->type = NEW_CMD;
	res->argv = argv;
	res->myenv = myenv;
	res->fd_in = -1;
	res->fd_out = -1;
	res->std_in = -1;
	res->std_out = -1;
	res->redirect = redirect;
	res->last_pipe_cmd = -1;
	res->herdoc = herdoc1;
	return ((t_cmd *)res);
}

t_cmd	*init_sub(t_cmd *root_sub, t_env **myenv, t_red *redirect,
		t_herdoc *herdoc)
{
	t_sub_sh	*res;

	res = (t_sub_sh *)malloc(sizeof(t_sub_sh));
	if (!res)
		return (NULL);
	res->type = SUB_SH;
	res->fd_in = -1;
	res->fd_out = -1;
	res->redirect = redirect;
	res->myenv = myenv;
	res->last_pipe_cmd = -1;
	res->herdoc = herdoc;
	res->sub_root = root_sub;
	return ((t_cmd *)res);
}
