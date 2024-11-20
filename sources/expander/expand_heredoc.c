/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:56 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/11 02:46:39 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	herdoc_newfd(int fd, t_env *myenv, int *last_status)
{
	char	*line;
	char	*tmp;
	int		fd_pipe[2];

	pipe(fd_pipe);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = line;
		line = split_word_var(line, myenv, last_status);
		free(tmp);
		if (line)
			ft_putstr_fd(line, fd_pipe[1]);
		else
			ft_putstr_fd("\n", fd_pipe[1]);
		free(line);
		line = NULL;
	}
	line = get_next_line(-1);
	close(fd_pipe[1]);
	close(fd);
	return (fd_pipe[0]);
}

char	*expand_filename(char *filename, t_env *env, int *last_status, int ref)
{
	char	*new;

	if (!filename || (filename && filename[0] == '\0'))
		ambiguous_exit(filename, ref);
	if (ft_strchr(filename, '$') == NULL)
		return (filename);
	new = split_word_var(filename, env, last_status);
	if (!new || count_arg(new) != 1)
	{
		ambiguous_exit(filename, ref);
		free(new);
		free(filename);
		return (NULL);
	}
	return (new);
}

int	count_arg(char *arg)
{
	char	*token;
	size_t	i;
	char	c;
	size_t	words;

	token = tokenizer(arg);
	c = ' ';
	words = 0;
	i = 0;
	if (*arg == '\0')
		return (free(token), 0);
	while (arg[i] == c && token[i] == 'w')
		i++;
	while (arg[i])
	{
		if (arg[i] == c && arg[i + 1] != c && token[i] == 'w')
			words++;
		i++;
	}
	if (arg[i - 1] != c && token[i] != 'w')
		words++;
	free(token);
	return (words);
}

void	mini_expander(t_node **head, t_env *env, int *st)
{
	t_node	*tmp;
	char	*tmpstr;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == 'w' || tmp->type == 'd')
		{
			tmpstr = tmp->str;
			tmp->str = split_word_var(tmp->str, env, st);
			if (tmpstr != tmp->str)
				free(tmpstr);
		}
		tmp = tmp->next;
	}
	return ;
}

void	add_node(t_node **head, t_node **tail, t_node *node)
{
	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		(*tail)->next = node;
	}
	*tail = node;
}
