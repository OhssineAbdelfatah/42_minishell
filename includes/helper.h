/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:45:53 by ilaasri           #+#    #+#             */
/*   Updated: 2024/11/11 04:06:13 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include "struct.h"
# include "norm_structs.h"

// PARSE THINGS :
/********************************************/

int		is_special(char s);
int		get_next_quote(char *s, int i);
char	**fr9_trb7(char *s);
int		dstr_len(char **s);
int		_check_tokens(char **tokens);
int		next_nonspecial(char *s, int i);

/*********************************** */
// TOKENS PART 2
/***************************** */

int		get_endo(char *s, int x);
int		get_starto(char *s, int x);
int		red_or_pipe(char c);

/********************************************** */
// 	COUNTING TOOLS
/********************************************** */
int		get_next_parenties(char *s, int i);
int		total_sub(char *s);

/****************************************** */
// COUNTING THINGS :
/********************************************/

int		counts_and_or(char *s);
int		count_red(char *s, t_count_pipe_red *var);
int		count_pipe_red(char *s);
int		counts_and_or(char *s);
int		count_sub_sh(char *s);

/****************************************** */
// PARSING SUB SHELL:
/********************************************/

int		check_tok_sub(char **tokens);
int		get_end_sub(char **tokens, int i);

/*********************************** */
// TOOLS ABT WHITE SPACES
/***************************** */

int		is_white(int c);
int		is_white_str(char *s);
int		is_full_white_str(char *s);

/****************************** */
// CONSTRACTORS :
/**************************************/

t_cmd	*init_new_cmd(char **argv, t_env **myenv, t_red *redirect,
			t_herdoc *herdoc);
t_cmd	*init_sub(t_cmd *root_sub, t_env **myenv, t_red *redirect,
			t_herdoc *herdoc);
t_cmd	*init_or(t_cmd *left, t_cmd *right);
t_cmd	*init_and(t_cmd *left, t_cmd *right);
t_cmd	*init_pipe(t_cmd *left, t_cmd *right);

/****************************************************/

// CONSTRACTORS TOOLS:
/***********************************************/
// void herdoc_content(t_cmd *herd);

t_cmd	*init_redire(t_cmd *cmd, char *file, int mode, int fd);
t_cmd	*init_herdoc(t_cmd *cmd, char *deliminater);
t_red	*get_red(char **tokens, int i, t_herdoc *herdoc);
t_red	*get_red_for_sub(char **tokens, int i);
t_red	*creat_red_lst(char **tokens, int i);

/***********************************************/

int		get_next_parenties_d(char **s, int i);

// char	**tokens(char *str);
int		_check_str(char *s);
int		check_qoutes(char *s);
void	print_tree(t_cmd *res);
int		which_one(char *s);
// int skip_nonspaces(char *str, int i);
//  char *ft_substr(char *str, int start, int end)

// new  MODIFICATION :
int		get_type(char **tokens, int i);
int		get_mode(char **tokens, int i);
// t_red *get_red(char **tokens, int i);
// t_red *get_red(char **tokens, int i, int *herdoc_pipe);
char	*cmd_line(char **tokens, int *x);
// t_cmd *init_new_cmd(char *argv, char **env, t_red *redirect);
// t_cmd *init_new_cmd(char **argv, t_env *myenv,t_red *redirect,
// int herdoc_pipe);
void	add_to_lst(t_red *red_lst, char **tokens, int i);
t_red	*creat_red_lst(char **tokens, int i);
// t_cmd *parse_new_exec(char **tokens, int *i, t_env **myenv);
void	add_to_lst(t_red *red_lst, char **tokens, int i);

// PARSE AST NODES:
/********************************************************** */
t_cmd	*root(char **tokens, t_env **env);
t_cmd	*parse_new_exec(char **tokens, int *i, t_env **myenv);
t_cmd	*parse_pipe_loop(char **tokens, int *i, t_env **myenv);
t_cmd	*parse_and_or(char **tokens, int *i, t_env **myenv);
t_cmd	*parse_pipe_rec(char **tokens, int *i, t_env **myenv);
t_cmd	*parse_sub(char **tokens, int *i, t_env **myenv);
/************************************************************** */

/*******************************************/
// 	BUILTING THE TREE TOOLS :
/*******************************************/
int		is_pipe(char *s);
int		is_and_or(char *s);

// new EXEC
/************************************ */

int		exec_sub_sh(t_cmd *cmd, int *last_status);
int		exec_or(t_cmd *cmd, int *last_status);
int		exec_and(t_cmd *cmd, int *last_status);
int		new_exec(t_cmd *cmd, int *last_status);
void	handle_error(t_cmd_exec *p, char **abs_path);
int		open_file(t_red *redirect, int *std[4], t_herdoc *herdoc, t_env *env);
void	open_herdoc(t_red *redirect, int *std[4], t_herdoc *herdoc, t_env *env);
void	left_child_is_sub(t_cmd *left_cmd, t_execp *sp, int *last_status);
int		exec_pipe(t_cmd *cmd, int *last_status);
int		execute_pipe(t_cmd *cmd, int *last_status);
int		recursion_pipe(t_cmd *cmd, int *last_status);
int		exec_new_cmd(t_cmd *cmd, int *last_status);

int		exec_red(t_red *redirect, int *std[4], t_herdoc *herdoc, t_env *env);
int		check_is_abs(char *cmd);
char	*cmd_abs_path(char *path, char *cmd);
/************************************ */

// SIGNALS
/************************************** */
void	do_nothing(int signal);
void	signal_handler(int signal);
/**************************************** */

// HERDOC
/*************************************************** */
int		get_herdoc(char **tokens, int i, t_herdoc *herdoc);
t_del	*first_del(t_del *node, char *value);
t_del	*add(t_del *node, char *value);
void	assign_her_exp(t_del *lst, t_herdoc *herdoc);
void	print_del(t_del *head);
/****************************************************** */

// ALWAYS FREE
/********************************** */
void	free_red_lst(t_red **lst);
void	free_new_cmd(t_cmd *cmd);
void	free_pipe2(t_cmd *cmd);
void	free_or(t_cmd *cmd);
void	free_and(t_cmd *cmd);
void	free_sub(t_sub_sh *cmd);
void	free_delimiters(t_del *head);
void	free_tree2(t_cmd *cmd);
void	free_mynigga(char **str);
void	free_dawgs(int how_many, ...);
// void free_tree(t_cmd *cmd);

/************************************* */

// ERROR
/****************** */
void	error(char *s, int er_num);
void	ambiguous_exit(char *str, int ref);
void	error_exec_new(char *str, int exit_status);
/************************ */
// PRINTER
/*************************/
void	my_dprint(int fd, char *s, ...);

/************************************************/
//   KJJK
/**************************************************/
int		check_err_red(t_red *redirect, char *file_name, int *std[4]);
#endif
