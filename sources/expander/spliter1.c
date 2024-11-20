/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:13 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:15:10 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**join_no_split(t_argv *args)
{
	int		i;
	char	**org_av;
	char	*tmp_av;

	org_av = args->orginal;
	i = -1;
	while (args)
	{
		tmp_av = org_av[++i];
		org_av[i] = ft_strdup(args->str);
		free(tmp_av);
		args = args->next;
	}
	org_av[++i] = NULL;
	return (org_av);
}

char	**join_args(t_argv *args)
{
	int		i;
	int		i_subarg;
	int		i_newargv;
	char	**new_argv;

	i = count_new_argv(args);
	new_argv = malloc((i + 1) * sizeof(char *));
	i_newargv = -1;
	while (args)
	{
		i_subarg = -1;
		if (args->str_splited)
		{
			while (args->str_splited[++i_subarg])
				new_argv[++i_newargv] = ft_strdup(args->str_splited[i_subarg]);
		}
		else
			new_argv[++i_newargv] = ft_strdup(args->str);
		args = args->next;
	}
	new_argv[++i_newargv] = NULL;
	return (new_argv);
}

int	skip_space_in_word(char *arg, int start)
{
	int		i;
	char	*token;

	token = tokenizer(arg);
	if ((size_t)start > ft_strlen(arg))
	{
		free(token);
		return ((int)ft_strlen(arg));
	}
	i = 0;
	while (arg[i + start])
	{
		if (arg[i + start] == ' ' && token[i + start] == 'w')
			i++;
		else
		{
			free(token);
			return (i + start);
		}
	}
	free(token);
	return (i + start);
}

int	skip_char(char *arg, int start)
{
	int		i;
	char	*token;

	token = tokenizer(arg);
	i = 0;
	while (arg[i + start])
	{
		if ((arg[i + start] == ' ' && token[i + start] == 'w'))
		{
			free(token);
			return (i + start);
		}
		i++;
	}
	free(token);
	return (i + start);
}

char	*mini_joiner(t_node *head)
{
	t_node	*tmp;
	char	*new;
	char	*tmp_new;

	tmp = head;
	new = ft_strdup("");
	while (tmp)
	{
		tmp_new = new;
		new = ft_strjoin(new, tmp->str);
		free(tmp_new);
		tmp = tmp->next;
	}
	free_lst(head);
	return (new);
}
