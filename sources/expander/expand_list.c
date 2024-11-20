/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:01 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:15:01 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_inside_arg(t_node **head)
{
	t_node	*tmp;
	t_node	*head2;
	t_node	*tail;
	char	**args;
	int		i;

	tail = NULL;
	head2 = NULL;
	args = ft_split((*head)->str, ' ');
	i = -1;
	while (args[++i])
	{
		tmp = create_node(ft_strdup(args[i]), 'w');
		add_node(&head2, &tail, tmp);
	}
	free_lst(*head);
	*head = head2;
}

void	__add_node(char *token, t_node **head, char type, t_node **tail)
{
	t_node	*node;

	node = create_node(token, type);
	add_node(head, tail, node);
}

char	*split_word_var(char *value, t_env *env, int *st)
{
	t_split_arg	dt;

	dt.head = NULL;
	while (value)
	{
		dt.start = ft_strchr(value, '$');
		if (dt.start && *(dt.start + 1))
		{
			dt.token = ft_strndup(value, dt.start - value);
			__add_node(dt.token, &dt.head, '0', &dt.tail);
			dt.token = ft_strndup(dt.start, ft_name(dt.start) - dt.start);
			if (ft_strlen(dt.token) == 1 && *dt.token == '$')
				dt.node = create_node(dt.token, '0');
			else
				dt.node = create_node(dt.token, '1');
			add_node(&dt.head, &dt.tail, dt.node);
			value = ft_name(dt.start);
		}
		else
		{
			__add_node(ft_strdup(value), &dt.head, '0', &dt.tail);
			break ;
		}
	}
	return (expand(&dt.head, env, st));
}

char	*__expand_joiner(t_node **head)
{
	t_expn	dt;

	dt.tmp = *head;
	dt.new = ft_strdup("");
	while (dt.tmp)
	{
		dt.tmpstr = dt.new;
		dt.new = ft_strjoin(dt.new, dt.tmp->str);
		free(dt.tmpstr);
		dt.tmp = dt.tmp->next;
	}
	return (dt.new);
}

char	*expand(t_node **head, t_env *env, int *st)
{
	t_expn	dt;

	dt.tmp = *head;
	while (dt.tmp)
	{
		if (dt.tmp->type == '1')
		{
			dt.value = get_env_value(env, dt.tmp->str + 1);
			if (ft_strcmp(dt.tmp->str + 1, "?"))
			{
				free(dt.value);
				dt.value = ft_itoa(*st);
			}
			dt.tmpstr = dt.tmp->str;
			if (dt.value)
				dt.tmp->str = ft_strdup(dt.value);
			else
				dt.tmp->str = ft_strdup("");
			free(dt.tmpstr);
			free(dt.value);
		}
		dt.tmp = dt.tmp->next;
	}
	dt.new = __expand_joiner(head);
	return (free_lst(*head), dt.new);
}
