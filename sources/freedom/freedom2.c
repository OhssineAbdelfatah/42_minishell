/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:59:59 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 19:00:00 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_delimiters(t_del *head)
{
	t_del	*tmp;

	while (NULL != head)
	{
		tmp = head->next;
		free(head->del);
		head->del = NULL;
		free(head);
		head = NULL;
		head = tmp;
	}
}

void	free_env_lst(t_env **lst)
{
	t_env	*tmp;

	tmp = (*lst)->next;
	while (NULL != *lst)
	{
		tmp = (*lst)->next;
		free((*lst)->value);
		free((*lst)->key);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_red_lst(t_red **lst)
{
	t_red	*tmp;

	tmp = (*lst)->next;
	while (NULL != *lst)
	{
		tmp = (*lst)->next;
		free((*lst)->file);
		(*lst)->file = NULL;
		free(*lst);
		*lst = NULL;
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_mynigga(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
	}
	free(str);
	str = NULL;
}

void	free_tree2(t_cmd *cmd)
{
	t_sub_sh	*tmp;

	if (!cmd)
		return ;
	if (cmd->type == NEW_CMD)
		free_new_cmd(cmd);
	else if (cmd->type == PIPE)
		free_pipe2(cmd);
	else if (cmd->type == AND)
		free_and(cmd);
	else if (cmd->type == OR)
		free_or(cmd);
	else if (cmd->type == SUB_SH)
	{
		tmp = (t_sub_sh *)cmd;
		free_tree2(tmp->sub_root);
		free_sub(tmp);
	}
}
