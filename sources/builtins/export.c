/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:56 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 18:17:14 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_exist(char *key, t_env *node)
{
	while (node != NULL)
	{
		if (ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_env	*creat_new_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->key = key;
	node->value = value;
	return (node);
}

int	export_body(t_env **env, char *key, char *argv)
{
	t_env	*tmp;
	char	*value;

	tmp = env_exist(key, *(env));
	value = get_value(argv);
	if (tmp)
	{
		update_env(tmp, value);
		free(key);
	}
	else
	{
		tmp = creat_new_env(key, ft_strdup(value));
		add_back_env(env, tmp);
		free(value);
	}
	return (0);
}

int	export(t_cmd_exec *p)
{
	int		status;
	char	*key;
	int		i;

	status = 0;
	if (ft_strslen(p->argv) == 1)
		return (print_export(*(p->myenv)), status);
	i = 0;
	while (p->argv[++i])
	{
		key = get_key(p->argv[i]);
		if (key && is_valid(key))
			export_body(p->myenv, key, p->argv[i]);
		else if (!is_valid(key))
		{
			status = 1;
			my_dprint(2, "minishell: export: `%s': not a valid identifier\n",
				p->argv[i]);
			free(key);
		}
	}
	return (status);
}
