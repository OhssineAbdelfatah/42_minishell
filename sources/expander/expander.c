/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:06 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/11 02:48:58 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_split_arg	init_spliter(t_split_arg data, char *str)
{
	data.head = NULL;
	data.tail = NULL;
	data.start = str;
	data.indx = 0;
	data.token = tokenizer(str);
	data.prev_char = data.token[0];
	return (data);
}

t_node	*split_argv(char *str)
{
	t_split_arg	dt;
	int			i;

	dt = (t_split_arg){0};
	dt = init_spliter(dt, str);
	i = -1;
	while (dt.token[++i])
	{
		if (dt.token[i] != dt.prev_char && i > 0)
		{
			dt.tmpdup = ft_strndup(dt.start, str + i - dt.start);
			dt.node = create_node(dt.tmpdup, dt.prev_char);
			add_node(&(dt.head), &(dt.tail), dt.node);
			dt.start = str + i;
			dt.indx = i;
		}
		if (dt.token[dt.indx] == dt.token[i] && dt.token[i + 1] == '\0')
		{
			dt.tmpdup = ft_strndup(dt.start, str + i - dt.start + 1);
			dt.node = create_node(dt.tmpdup, dt.prev_char);
			add_node(&(dt.head), &(dt.tail), dt.node);
		}
		dt.prev_char = dt.token[i];
	}
	return (free(dt.token), (dt.head));
}

char	**joiner(t_argv *args, t_env *env, int *st, int type)
{
	t_argv	*tmp;
	char	**new;
	char	*tmp_str;

	new = NULL;
	tmp = args;
	while (tmp)
	{
		tmp->arg = split_argv(tmp->str);
		mini_expander(&(tmp->arg), env, st);
		tmp_str = tmp->str;
		tmp->str = mini_joiner(tmp->arg);
		free(tmp_str);
		tmp = tmp->next;
	}
	spliter_args(args);
	new = join_args(args);
	if (RED_EXPN == type && (ft_strslen(new) > 1
			|| ft_strslen(new) == 0))
		ambiguous_exit(args->str, 0);
	return (new);
}

int	should_expand(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '$'))
			return (1);
		i++;
	}
	return (0);
}

char	**expander(char **argv, t_env *env, int *st, int type)
{
	char	**new_argv;
	t_argv	*args;

	if (!argv || !(*argv))
		return (NULL);
	if (0 == should_expand(argv))
		return (argv);
	args = argv_to_lst(argv);
	new_argv = joiner(args, env, st, type);
	free_argv_lst(args, type);
	free(argv);
	return (new_argv);
}
