/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:50 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 16:35:41 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_env(t_env *env)
{
	while (env != NULL)
	{
		if (env->key && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	add_back_env(t_env **head, t_env *node)
{
	t_env	*tmp;

	if (node == NULL)
		return ;
	if (!head)
		return ;
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

t_env	*creat_env(char *env_main)
{
	t_env	*node;
	char	**key;
	char	*value;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	key = ft_split(env_main, '=');
	node->key = ft_strdup(key[0]);
	free_split(key);
	value = ft_strchr(env_main, '=');
	node->value = NULL;
	if (value != NULL)
	{
		value++;
		node->value = ft_strdup(value);
	}
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **env_main)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = -1;
	env = NULL;
	while (env_main && env_main[++i])
	{
		if (ft_strnstr(env_main[i], "OLDPWD", 6) == NULL)
		{
			tmp = creat_env(env_main[i]);
			add_back_env(&env, tmp);
		}
	}
	return (env);
}
