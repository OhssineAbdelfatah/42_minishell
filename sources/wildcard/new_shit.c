/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:05:06 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 20:05:08 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_slash(char *av, int i)
{
	while (av[i] && av[i] == '/')
		i++;
	return (i);
}

int	next_slash(char *av, int i)
{
	while (av[i] && av[i] != '/')
		i++;
	return (i);
}

char	**the_one(char *av, int which_time, int start)
{
	char	**ret;
	char	*first;
	int		begin;
	int		i;
	int		j;

	start = skip_slash(av, 0);
	j = next_slash(av, i);
	if (i == j)
		return (NULL);
	first = ft_substr(av, i, next_slash(av, i) + 1);
	ret = treat(first);
	if (!ret)
		return (NULL);
	ret = joinin(ret, av, j);
	begin = find_start(ret, start);
	return (ret);
}
