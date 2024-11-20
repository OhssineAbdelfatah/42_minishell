/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstoarry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:58 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:13:56 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(t_env *root)
{
	int	i;

	i = 0;
	while (root)
	{
		i++;
		root = root->next;
	}
	return (i);
}

char	**lstoarry(t_env *root)
{
	char	**env_arr;
	char	*single_env;
	char	*tmp;
	int		env_len;
	int		i;

	env_len = env_size(root);
	i = -1;
	if (env_len == 0)
		return (NULL);
	env_arr = malloc(sizeof(char *) * (env_len + 1));
	if (!env_arr)
		return (NULL);
	while (++i < env_len)
	{
		single_env = ft_strjoin(root->key, "=");
		tmp = single_env;
		single_env = ft_strjoin(single_env, root->value);
		free(tmp);
		env_arr[i] = ft_strdup(single_env);
		free(single_env);
		root = root->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}
