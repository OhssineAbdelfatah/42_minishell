/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:09:04 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/10 23:17:06 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_dprint(int fd, char *s, ...)
{
	va_list	lst;
	int		i;

	i = 0;
	va_start(lst, s);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == 's')
		{
			ft_putstr_fd(va_arg(lst, char *), fd);
			i++;
		}
		else
			write(fd, &s[i], 1);
		if (s[i])
			i++;
	}
	va_end(lst);
}
