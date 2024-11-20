/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:13:47 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:33:00 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env(t_env *node, char *value)
{
	free(node->value);
	if (value == NULL)
		node->value = ft_strdup("");
	else
		node->value = value;
	return ;
}

void	print_export(t_env *env)
{
	while (env != NULL)
	{
		printf("declare -x %s=\"", env->key);
		if (env->value)
			printf("%s", env->value);
		printf("\"\n");
		env = env->next;
	}
}

char	*get_key(char *arg)
{
	char	*eql;

	eql = ft_strchr(arg, '=');
	if (!eql)
		return (ft_strdup(arg));
	eql = ft_strndup(arg, eql - arg);
	return (eql);
}

char	*get_value(char *arg)
{
	char	*eql;

	eql = ft_strchr(arg, '=');
	if (!eql)
		return (NULL);
	eql = ft_strdup(eql + 1);
	return (eql);
}
