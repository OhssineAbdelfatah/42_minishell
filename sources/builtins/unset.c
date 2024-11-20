/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:00 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:14:00 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	destroy_single_env(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

bool	is_valid(char *key)
{
	int	i;

	i = 0;
	if (key[i] != '_' && !ft_isalpha(key[i]))
		return (false);
	while (key[++i])
	{
		if (!ft_isdigit(key[i]) && !ft_isalpha(key[i]) && key[i] != '_')
			return (false);
	}
	return (true);
}

int	unset_body(t_env *tmp, char *key, t_env *prev, t_env **head)
{
	int	status;

	status = 0;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) && is_valid(key))
		{
			if (prev == NULL)
				*head = tmp->next;
			else
				prev->next = tmp->next;
			destroy_single_env(tmp);
			tmp = NULL;
			break ;
		}
		else if (!is_valid(key))
		{
			my_dprint(2, "minishell: unset: `%s': not a valid identifier\n",
				key);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	unset_env(t_env **head, char **key)
{
	t_env	*tmp;
	t_env	*prev;
	int		status;
	int		i;

	status = 0;
	if (!head || !(*head))
		return (status);
	i = 0;
	while (key[++i])
	{
		tmp = *head;
		prev = NULL;
		status = unset_body(tmp, key[i], prev, head);
	}
	return (status);
}
