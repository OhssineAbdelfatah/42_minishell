/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:53:02 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/26 19:53:06 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dir_cont	*creat_node(char *value, char *work_dir)
{
	t_dir_cont	*node;
	char		*s;

	node = (t_dir_cont *)malloc(sizeof(t_dir_cont));
	if (!node)
		panic("malloc faild !\n");
	node->next = NULL;
	node->working_direc = ft_strdup(work_dir);
	node->value = ft_strdup(value);
	s = ft_strjoin(work_dir, value);
	node->type = ALL_KINDS;
	if (valid_dir(s))
		node->type = DIREC;
	free(s);
	node->hidden = 0;
	if (value[0] == '.')
		node->hidden = 1;
	node->valid = 0;
	return (node);
}

void	add_to_lst_dir(t_dir_cont **head, t_dir_cont *new_node)
{
	t_dir_cont	*tmp;

	tmp = *head;
	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_dir_cont	*array_to_lst_dir(char **av, char *work_dir)
{
	t_dir_cont	*head;
	int			i;

	i = 0;
	head = NULL;
	if (!av)
		return (NULL);
	while (av[i])
	{
		add_to_lst_dir(&head, creat_node(av[i], work_dir));
		i++;
	}
	return (head);
}

void	free_dir_lst(t_dir_cont **head)
{
	t_dir_cont	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->value);
		free((*head)->working_direc);
		free(*head);
		*head = tmp;
	}
}

// void print_dir_lst(t_dir_cont *head)
// {
//     if (!head)
//     {
//         printf("NADA !\n");
//         return ;
//     }
//     while (head)
//     {
//         printf("val :%s, type : %d, valid %d\n", head->value, head->type,
// head->valid);
//         head = head->next;
//     }
// }
