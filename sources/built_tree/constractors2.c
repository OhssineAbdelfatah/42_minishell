/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constractors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:49:13 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 13:49:15 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**new_str(char **old_str)
{
	char	**res;
	int		i;
	int		old_len;

	i = 0;
	old_len = dstr_len(old_str);
	res = (char **)malloc(sizeof(char *) * (old_len + 2));
	if (NULL == res)
		return (NULL);
	if (old_str)
	{
		while (i < old_len)
		{
			res[i] = ft_strdup(old_str[i]);
			i++;
		}
	}
	res[i] = NULL;
	free_mynigga(old_str);
	return (res);
}

t_red	*creat_red_lst(char **tokens, int i)
{
	t_red	*res;

	res = (t_red *)malloc(sizeof(t_red));
	if (!res)
		return (NULL);
	res->type = get_type(tokens, i);
	res->mode = get_mode(tokens, i);
	if (res->mode == 4 || res->type == HERDOC)
		res->fd = 0;
	else
		res->fd = 1;
	i++;
	res->file = ft_strdup(tokens[i]);
	res->next = NULL;
	return (res);
}

void	add_to_lst(t_red *red_lst, char **tokens, int i)
{
	t_red	*new_red;
	t_red	*tmp;

	new_red = NULL;
	tmp = red_lst;
	new_red = creat_red_lst(tokens, i);
	if (NULL == new_red)
		return ;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new_red;
}
