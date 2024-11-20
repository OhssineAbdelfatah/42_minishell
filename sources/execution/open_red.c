/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:20:54 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/10 23:14:34 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_input_file(t_red *redirect, int *std[4], t_env *env)
{
	redirect->file = expand_filename(redirect->file, env, std[3], *std[2]);
	if (!redirect->file)
		return (1);
	redirect->file = wild_expand_red(redirect->file, *std[2]);
	if (!redirect->file)
		return (1);
	*std[0] = open(redirect->file, O_RDONLY);
	if (*std[0] < 0)
	{
		my_dprint(2, "minishell: %s:No such file or directory\n",
			redirect->file);
		if (*std[2])
			panic("");
		return (1);
	}
	return (0);
}

int	open_outfile_trunc(t_red *redirect, int *std[4], t_env *env)
{
	redirect->file = expand_filename(redirect->file, env, std[3], *std[2]);
	if (!redirect->file)
		return (1);
	redirect->file = wild_expand_red(redirect->file, *std[2]);
	if (!redirect->file)
		return (1);
	*std[1] = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (0);
}

int	open_file_append(t_red *redirect, int *std[4], t_env *env)
{
	redirect->file = expand_filename(redirect->file, env, std[3], *std[2]);
	if (!redirect->file)
		return (1);
	redirect->file = wild_expand_red(redirect->file, *std[2]);
	if (!redirect->file)
		return (1);
	*std[1] = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (0);
}

int	non_herdoc(t_red *redirect, int *std[4], t_env *env, t_open_file *var)
{
	if (check_err_red(redirect, var->file_name, std))
		return (1);
	if (77 == redirect->mode)
		var->status = open_file_append(redirect, std, env);
	else if (7 == redirect->mode)
		var->status = open_outfile_trunc(redirect, std, env);
	else if (4 == redirect->mode)
		var->status = open_input_file(redirect, std, env);
	if (var->status == 1)
		return (free(var->file_name), var->status);
	if (*std[1] < 0 && 4 != redirect->mode)
	{
		my_dprint(2, "minishell: %s: Permission denied\n", redirect->file);
		if (*std[2] != SIMPLE)
			panic("");
		else
			return (free(var->file_name), 1);
	}
	return (0);
}

int	open_file(t_red *redirect, int *std[4], t_herdoc *herdoc, t_env *env)
{
	t_open_file	var;

	var.status = 0;
	var.file_name1 = ft_strdup(redirect->file);
	var.file_name = whithout_quotes(var.file_name1, 1);
	if (HERDOC == redirect->type)
		open_herdoc(redirect, std, herdoc, env);
	else
	{
		if (non_herdoc(redirect, std, env, &var))
			return (1);
	}
	free(var.file_name);
	return (var.status);
}
