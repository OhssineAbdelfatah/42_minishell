/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_red2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:22:03 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/10 00:22:04 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_err_red(t_red *redirect, char *file_name, int *std[4])
{
	if (ft_strlen(file_name) == 0)
	{
		ft_putstr_fd("minishell: no such file or directory\n", 2);
		if (*std[2])
			exit(1);
		return (free(file_name), 1);
	}
	if (*std[1] != -1 && (77 == redirect->mode || 7 == redirect->mode))
		close(*std[1]);
	if (*std[0] != -1 && 4 == redirect->mode)
		close(*std[0]);
	return (0);
}
