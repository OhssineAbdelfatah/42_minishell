/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_expand_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:55:33 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/05 22:55:34 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_new_args_red(char *old, t_dir_cont *dir_cont, int *index)
{
	int	ret;
	int	nbr_mtches;

	ret = 0;
	if (is_it_wild(old))
	{
		nbr_mtches = count_matches(old, dir_cont);
		if (nbr_mtches > 0)
		{
			ret += nbr_mtches;
			*index = 1;
		}
		else
			ret++;
		reset_validation(dir_cont);
	}
	else
		ret++;
	return (ret);
}

char	*wild_expand_red(char *old, int ref)
{
	t_wild_expand	var;

	if (is_it_wild(old) == 0)
		return (whithout_quotes(old, 1));
	var.work_dir = get_work_direc();
	var.dir_cont_array = all_dir_sorted(var.work_dir);
	var.dir_cont = array_to_lst_dir(var.dir_cont_array, var.work_dir);
	var.new_len = count_new_args_red(old, var.dir_cont, &(var.i));
	if (var.new_len > 1)
	{
		ambiguous_exit(old, ref);
		if (ref == SIMPLE)
			return (free(old), freedom(&(var.dir_cont_array), &(var.dir_cont),
					&(var.work_dir)), NULL);
	}
	if (var.new_len < 0 || var.i == 0)
		return (freedom(&(var.dir_cont_array), &(var.dir_cont),
				&(var.work_dir)), whithout_quotes(old, 1));
	var.new = (get_new_args(&old, var.new_len, var.dir_cont));
	free(old);
	var.new_for_red = ft_strdup(var.new[0]);
	free_mynigga(var.new);
	return (freedom(&(var.dir_cont_array), &(var.dir_cont), &(var.work_dir)),
		var.new_for_red);
}
