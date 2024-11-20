/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:23 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/11 02:48:16 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

typedef enum s_expan
{
	CMD_EXPN,
	HERDOC_EXPN,
	RED_EXPN
}					t_expan;

typedef enum s_exec_bltn
{
	SIMPLE,
	NOT_SIMPLE
}					t_exec_bltn;

typedef struct s_node
{
	char			*str;
	char			type;
	struct s_node	*next;
}					t_node;

typedef struct s_argv
{
	t_node			*arg;
	char			*str;
	char			**str_splited;
	int				len;
	char			**orginal;
	struct s_argv	*next;
}					t_argv;

typedef struct s_split_arg
{
	char			*token;
	char			prev_char;
	t_node			*head;
	t_node			*tail;
	t_node			*node;
	char			*tmpdup;
	char			*start;
	int				indx;
}					t_split_arg;

typedef struct s_expn
{
	t_node			*tmp;
	char			*new;
	char			*value;
	char			*tmpstr;
}					t_expn;

typedef struct s_tokens_exp
{
	bool			in_d;
	bool			in_s;
	char			prv_chr;
	int				i;
}					t_tokens;

char				**expander(char **argv, t_env *env, int *last_status,
						int type);
char				*tokenizer(char *arg);
t_node				*split_argv(char *str);
char				**joiner(t_argv *args, t_env *env, int *st, int type);

t_node				*create_node(char *value, char type);
void				add_node(t_node **head, t_node **tail, t_node *node);
char				*split_word_var(char *value, t_env *env, int *st);
void				mini_expander(t_node **head, t_env *env, int *st);
char				*expand(t_node **head, t_env *env, int *st);

char				*ft_name(char *arg);
void				free_lst(t_node *head);
char				*clean_qts(char *str);

int					herdoc_newfd(int fd, t_env *myenv, int *last_status);

void				add_argv(t_argv **head, t_argv **tail, t_argv *arg);
t_argv				*create_argv(t_node *head, char *str, char **argv);

void				free_argv_lst(t_argv *head, int type);
t_argv				*argv_to_lst(char **argv);
int					count_new_argv(t_argv *tmp);
void				spliter_args(t_argv *args);
char				**split_arg(char *arg);

int					count_arg(char *arg);
char				**join_no_split(t_argv *args);
char				**join_args(t_argv *args);
int					skip_space_in_word(char *arg, int start);
int					skip_char(char *arg, int start);

int					should_expand(char **argv);
char				*mini_joiner(t_node *head);
char				*expand_filename(char *filename, t_env *env,
						int *last_status, int source);
void				add_node(t_node **head, t_node **tail, t_node *node);

#endif