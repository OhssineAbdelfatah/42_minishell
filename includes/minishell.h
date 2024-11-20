/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:43:17 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/11 03:59:46 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <stdarg.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "helper.h"
# include "helper2.h"
# include "colors.h"
# include "builtins.h"
# include "expander.h"
# include "../lib/libft/libft.h"
# include "../lib/gnl0/get_next_line.h"

# define GRN "\e[0;32m"
# define CYNB "\e[46m"
# define CRESET "\e[0m"

extern int	g_sig;

///////////////////////////////
///////////      DEBUG       //
///////////////////////////////

// void		debug_free(void *ptr);
// void		*debug_malloc(size_t size);

///////////////////////////////
///////////      DEBUG       //
///////////////////////////////

/*Testing a new split shit */
int			count_tokens_new(char *s);
///////that's it ///

int			skip_spaces(char *s, int x);
void		exec_cmd(char **tokens, char **env);
void		panic(char *str);
int			ft_strlen1(char *s);
char		**split_shit(char *s);
char		*get_env_value(t_env *env, char *key);
// void exec(t_cmd *cmd);

// debug
void		pexit(char *s);

#endif
