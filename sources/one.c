/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:37:40 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:19:35 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_sig;

void	panic(char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	exit(1);
}

void	parse_nd_exec(char **my_tokens, t_env **dup_env, int *status)
{
	t_cmd	*res;

	res = NULL;
	res = root(my_tokens, dup_env);
	if (!res)
		return ;
	if (g_sig == -1)
		*status = new_exec(res, status);
	if (g_sig == 130 || g_sig == 131)
	{
		*status = 130;
		if (g_sig == 131)
			*status = 1;
		g_sig = -1;
	}
	free_mynigga(my_tokens);
	free_tree2(res);
}

void	history(char *str)
{
	if (!str)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (!str || 0 == ft_strlen(str))
		return ;
	if (is_white_str(str))
		return ;
	add_history(str);
}

void	main_core(t_main *var)
{
	var->my_tokens = fr9_trb7(var->str);
	var->checker = _check_tokens(var->my_tokens);
	if (var->checker != EXEC && var->checker != SUB_SH)
	{
		free_mynigga(var->my_tokens);
		error(NULL, var->checker);
		var->status = 258;
	}
	else if (var->my_tokens)
		parse_nd_exec(var->my_tokens, &(var->dup_env), &(var->status));
}

int	main(int ac, char **av, char **env)
{
	t_main	var;

	var.status = 0;
	var.dup_env = init_env(env);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		var.str = readline(GRN "minishell> " CRESET);
		history(var.str);
		if (g_sig == 1300)
			var.status = 1;
		g_sig = -1;
		if (var.str && ft_strlen(var.str) && _check_str(var.str) == 0)
			main_core(&var);
		free(var.str);
	}
	(void)ac;
	(void)av;
}
