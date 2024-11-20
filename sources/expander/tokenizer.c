/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:36:16 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/10 23:15:13 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*initialize_tokens(int length)
{
	char	*tokens;
	int		i;

	tokens = ft_calloc(length + 1, sizeof(char));
	i = 0;
	while (i <= length)
	{
		tokens[i] = '0';
		i++;
	}
	return (tokens);
}

static int	__checker(t_tokens *tok)
{
	return (!tok->in_s && !tok->in_d && (tok->prv_chr == '\''
			|| tok->prv_chr == '\"' || tok->i == 0));
}

int	process_tokens(char *arg, char *tokens, t_tokens tok)
{
	while (arg[++tok.i])
	{
		if (arg[tok.i] == '\"' && !tok.in_s)
		{
			tokens[tok.i] = 'd';
			tok.in_d = !tok.in_d;
		}
		else if (arg[tok.i] == '\'' && !tok.in_d)
		{
			tokens[tok.i] = 's';
			tok.in_s = !tok.in_s;
		}
		else if (__checker(&tok))
			tokens[tok.i] = 'w';
		tok.prv_chr = arg[tok.i];
		if (tokens[tok.i] == '0')
		{
			tokens[tok.i] = 'w';
			if (tok.in_d)
				tokens[tok.i] = 'd';
			else if (tok.in_s)
				tokens[tok.i] = 's';
		}
	}
	return (tok.i);
}

char	*tokenizer(char *arg)
{
	int			len;
	t_tokens	tok;
	char		*tokens;

	len = ft_strlen(arg);
	tok.in_d = false;
	tok.in_s = false;
	tok.prv_chr = ' ';
	tok.i = -1;
	tokens = initialize_tokens(len);
	tokens[process_tokens(arg, tokens, tok)] = '\0';
	return (tokens);
}

t_node	*create_node(char *value, char type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->str = value;
	node->type = type;
	node->next = NULL;
	return (node);
}
