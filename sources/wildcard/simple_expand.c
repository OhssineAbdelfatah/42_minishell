/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:53:44 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:53:45 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_matches(char *old, t_dir_cont *dir_cont)
{
	int	ret;
	int	type;

	type = file_or_dir(old);
	check_validation(old, dir_cont, type);
	ret = is_there_a_match(dir_cont);
	return (ret);
}

int	count_new_args(char **old, t_dir_cont *dir_cont, int *index)
{
	int	ret;
	int	nbr_mtches;
	int	i;

	ret = 0;
	i = 0;
	while (old[i])
	{
		if (is_it_wild(old[i]))
		{
			nbr_mtches = count_matches(old[i], dir_cont);
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
		i++;
	}
	return (ret);
}

void	get_matches(char **new, char *needle, t_dir_cont *dir_cont, int *index)
{
	int	i;
	int	foundedlen;

	i = 0;
	foundedlen = count_matches(needle, dir_cont);
	if (foundedlen == 0)
		return ;
	while (i < foundedlen)
	{
		new[*index] = get_next_valid(dir_cont, i);
		i++;
		(*index)++;
	}
	reset_validation(dir_cont);
	return ;
}

char	**get_new_args(char **old, int new_len, t_dir_cont *dir_cont)
{
	t_new_args	var;

	var.i = 0;
	var.j = 0;
	var.new = (char **)malloc(sizeof(char *) * (new_len + 1));
	if (!var.new)
		panic("malloc failed !\n");
	while (var.i < new_len)
	{
		var.tmp = var.i;
		if (is_it_wild(old[var.j]))
		{
			get_matches(var.new, old[var.j], dir_cont, &(var.i));
			if (var.i == var.tmp)
				var.new[var.i] = whithout_quotes(ft_strdup(old[var.j]), 1);
		}
		else
			var.new[var.i] = whithout_quotes(ft_strdup(old[var.j]), 1);
		if (var.i == var.tmp)
			var.i++;
		var.j++;
	}
	var.new[var.i] = NULL;
	return (var.new);
}

char	**wild_expand(char **old)
{
	t_wild_expand	var;

	var.i = 0;
	if (is_it_wild_args(old) == 0)
		return (unquote_old(old, 1));
	var.work_dir = get_work_direc();
	var.dir_cont_array = all_dir_sorted(var.work_dir);
	var.dir_cont = array_to_lst_dir(var.dir_cont_array, var.work_dir);
	var.new_len = count_new_args(old, var.dir_cont, &(var.i));
	if (var.new_len < 0 || var.i == 0)
		return (freedom(&(var.dir_cont_array), &(var.dir_cont),
				&(var.work_dir)), unquote_old(old, 1));
	var.new = get_new_args(old, var.new_len, var.dir_cont);
	free_mynigga(old);
	return (freedom(&(var.dir_cont_array), &(var.dir_cont), &(var.work_dir)),
		var.new);
}

// int main(int ac, char **av)
// {
//     char **new, **old;
//     int i, avlen;
//     new = NULL;
//     if (ac == 1)
//         return(printf("more ARGS A zbi\n"));
//     avlen = dstr_len(av);
//     old = clone(av, avlen);
//     new = wild_expand(old);
//     i = 0;
//     while (new[i])
//     {
//         printf("New >>%s\n", new[i]);
//         i++;
//     }
//     avlen = dstr_len(new);
//     if (avlen > 2)
//         free_mynigga(new);
// }
