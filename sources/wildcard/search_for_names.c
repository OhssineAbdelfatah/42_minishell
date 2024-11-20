/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_names.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:53:30 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:53:31 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_there_a_match(t_dir_cont *head)
{
	t_dir_cont	*tmp;
	int			match;

	match = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->valid == 1)
			match++;
		tmp = tmp->next;
	}
	return (match);
}

void	reset_validation(t_dir_cont *head)
{
	t_dir_cont	*tmp;

	tmp = head;
	while (tmp)
	{
		tmp->valid = 0;
		tmp = tmp->next;
	}
}

void	check_validation(char *needle, t_dir_cont *head, int type)
{
	t_dir_cont	*tmp;
	t_globing	*glob;

	tmp = head;
	if (type == DIREC)
		needle = take_slash_of(needle);
	glob = wilding(needle);
	while (tmp)
	{
		if (0 == check_node_for_valid(glob, tmp, type))
			tmp->valid = 1;
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp)
	{
		if (needle[0] != '.' && tmp->valid == 1 && tmp->value[0] == '.')
			tmp->valid = 0;
		tmp = tmp->next;
	}
	if (type == DIREC)
		free(needle);
	freeglobing(&glob);
}

// the full path of a wrong dir
/// Users/ilaasri/Desktop/C_cursus/wilding/test_wild

// int main(int ac, char **av)
// {
//     t_dir_cont *head;
//     char **whatsin;
//     char *work_dir;
//     if (ac == 1)
//         return(printf("enter more args \n"), 1);
//     work_dir = get_work_direc();
//     whatsin = all_dir_sorted(work_dir);
//     head = array_to_lst_dir(whatsin, work_dir);
//     print_dir_lst(head);
//     printf("Needle : %s\n", av[1]);
//     check_validation(av[1], head, DIREC);
//     printf("#######################################\n");
//     printf("NUMBER OF MATCHES>>%d\n", is_there_a_match(head));
//     print_dir_lst(head);
//     free_mynigga(whatsin);
//     free_dir_lst(&head);
//     free(work_dir);
//     // (void)av;
//     // (void)head;
//     return (0);
// }
