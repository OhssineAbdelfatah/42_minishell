/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:20 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:15:15 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_name(char *arg)
{
	if (!arg)
		return (NULL);
	arg++;
	while (*arg)
	{
		if ((!ft_isalnum(*arg) && *arg != '_' && *arg != '?') || *arg == '\0')
			return (arg);
		arg++;
	}
	return (arg);
}

void	free_lst(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->str);
		free(head);
		head = tmp;
	}
}

char	*clean_qts(char *str)
{
	char	*new;

	if ((int)ft_strlen(str) < 3)
		new = ft_strdup("");
	else
		new = ft_strndup(str + 1, ft_strlen(str + 1) - 1);
	free(str);
	return (new);
}

t_argv	*create_argv(t_node *head, char *str, char **argv)
{
	t_argv	*arg;

	arg = malloc(sizeof(t_argv));
	arg->arg = head;
	arg->str = str;
	arg->len = 0;
	arg->orginal = argv;
	arg->str_splited = NULL;
	arg->next = NULL;
	return (arg);
}

void	add_argv(t_argv **head, t_argv **tail, t_argv *arg)
{
	if (*head == NULL)
		*head = arg;
	else
		(*tail)->next = arg;
	*tail = arg;
}
