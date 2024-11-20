/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:11 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:15:07 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_argv_lst(t_argv *head, int type)
{
	t_argv	*tmp;

	while (head)
	{
		tmp = head->next;
		if (type == CMD_EXPN || type == RED_EXPN)
			free(head->str);
		free_split(head->str_splited);
		free(head);
		head = tmp;
	}
}

t_argv	*argv_to_lst(char **argv)
{
	int		i;
	t_argv	*head;
	t_argv	*tail;
	t_argv	*node;

	tail = NULL;
	head = NULL;
	i = -1;
	while (argv[++i])
	{
		node = create_argv(NULL, argv[i], argv);
		add_argv(&head, &tail, node);
	}
	return (head);
}

int	count_new_argv(t_argv *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (tmp->len != 0)
			i += tmp->len;
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	spliter_args(t_argv *args)
{
	while (args)
	{
		if (args->str && count_arg(args->str) > 1)
		{
			args->str_splited = split_arg(args->str);
			args->len = ft_strslen(args->str_splited);
		}
		args = args->next;
	}
}

char	**split_arg(char *arg)
{
	char	**new_arg;
	int		i;
	int		j;
	int		looper;
	int		end;

	if (!arg)
		return (NULL);
	looper = skip_space_in_word(arg, 0);
	i = count_arg(arg);
	new_arg = malloc((i + 1) * sizeof(char *));
	j = -1;
	end = 0;
	while (++j < i)
	{
		end = skip_char(arg, looper + 1) + 1;
		new_arg[j] = ft_strndup(arg + looper, end - 1 - looper);
		looper = skip_space_in_word(arg, end);
	}
	new_arg[j] = NULL;
	return (new_arg);
}
