/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:23 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:14:28 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	__checker_handle_err(t_cmd_exec *p)
{
	return (p->argv[0] && (p->argv[0][0] == '/' || (p->argv[0][0] == '.'
		&& p->argv[0][1] == '/') || (p->argv[0][0] == '.'
		&& p->argv[0][1] == '.' && p->argv[0][2] == '/')));
}

void	__abs_path(t_cmd_exec *p, char **abs_path)
{
	*abs_path = get_env_value(*(p->myenv), "PATH");
	if (!(*abs_path))
		error_exec_new(p->argv[0], 1);
	*abs_path = cmd_abs_path(*abs_path, p->argv[0]);
	if (!abs_path)
		error_exec_new(p->argv[0], 127);
}

void	handle_error(t_cmd_exec *p, char **abs_path)
{
	struct stat	file;

	if (__checker_handle_err(p))
	{
		if (stat(p->argv[0], &file) == -1)
		{
			write(2, "minishell: no such file or directory\n", 38);
			exit(127);
		}
		else if (S_ISDIR(file.st_mode))
		{
			my_dprint(2, "minishell: %s is a directory\n", p->argv[0]);
			exit(126);
		}
		else if (S_ISREG(file.st_mode) && !(file.st_mode & S_IXUSR))
		{
			write(2, "minishell: permission denied\n", 30);
			exit(126);
		}
		else if (S_ISREG(file.st_mode) && file.st_mode & S_IXUSR)
			return (*abs_path = p->argv[0], (void)0);
	}
	else
		__abs_path(p, abs_path);
}
