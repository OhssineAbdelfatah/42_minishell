/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:58:17 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:58:19 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	get_next_wild(char *av, int i)
{
	while (av[i] && av[i] != '*')
	{
		if (av[i] == '\'' || av[i] == '"')
			i = get_next_quote(av, i);
		if (av[i])
			i++;
	}
	return (i);
}

char	**clone(char **av, int len)
{
	int		i;
	char	**res;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		panic("malloc failed !\n");
	while (i < len)
	{
		res[i] = ft_strdup(av[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
