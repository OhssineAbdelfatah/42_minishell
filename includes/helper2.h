/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:45:58 by ilaasri           #+#    #+#             */
/*   Updated: 2024/10/29 00:45:59 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER2_H
# define HELPER2_H

# include "struct.h"

/************************************** */
// SIMPLE CHECK DIR AND SORT OUTPUT
/*************************************** */
void		ft_swap_str(char **s1, char **s2);
int			get_len_of_dir(char *dir_name);
char		**all_dir_sorted(char *dir_name);
int			need_a_sort(char *a, char *b);
int			is_it_sorted(char **dir);
void		just_sort(char **dir);

/*************************** */
// CONVERT THE ARRAY TO A LIST WITH MORE INFOS:
/*************************** */
t_dir_cont	*array_to_lst_dir(char **av, char *work_dir);
t_globing	*add_glob_node(t_globing *head, t_globing *new);
t_globing	*create_glob_node(char *value, int pos);
void		freeglobing(t_globing **head);
void		print_dir_lst(t_dir_cont *head);
char		*in_which_dir(char *s);
int			lenofminiwild(char *arg);
void		treat_wild(char **ret, char *old_arg, int *j);
int			get_retlen(char **old_arg);
char		**new_args(char **old_arg);
int			valid_dir(char *dir_nmae);
int			is_it_wild_args(char **av);
int			is_it_wild(char *av);

/********************************************** */
// IF THE ARG ARE WILD CONVERT TO LIST
/************************************************* */

t_globing	*create_glob_node(char *value, int pos);
t_globing	*add_glob_node(t_globing *head, t_globing *new);
t_globing	*wilding(char *s);
void		freeglobing(t_globing **head);
void		print_glob(t_globing *head);

/********************************************** */
// GET WHAT'S IN THE DIRECTORY, SORT IT AND PUT IT IN A LIST
/********************************************** */

t_dir_cont	*creat_node(char *value, char *work_dir);
void		print_dir_lst(t_dir_cont *head);
void		add_to_lst_dir(t_dir_cont **head, t_dir_cont *new_node);
t_dir_cont	*array_to_lst_dir(char **av, char *work_dir);
void		free_dir_lst(t_dir_cont **head);

/*********************************** */
// JUST MORE USEFULL FUNCTIONS:
/********************************** */

int			is_quoted(char *s);
int			get_reslen(char *s);
char		*whithout_quotes(char *value, int to_free);

void		check_validation(char *needle, t_dir_cont *head, int type);
int			get_next_wild(char *av, int i);

/**************************** */
// LITTLE TOOLS :
/****************************** */
int			file_or_dir(char *s);
int			valid_dir(char *dir_nmae);

/************************************************/
// LLOKING FOR MATCHES
/************************************************/
int			is_there_a_match(t_dir_cont *head);
void		reset_validation(t_dir_cont *head);

/**************************************************** */
// TOOLS OF SIMPLE EXPAND :
/**************************************************** */
char		**clone(char **av, int len);
void		freedom(char ***dir_cont_array, t_dir_cont **dir_cont,
				char **working);
void		printd(char **av);
void		print_valid_ones(t_dir_cont *head);
char		*get_next_valid(t_dir_cont *dir_cont, int index);
char		*get_work_direc(void);
char		**unquote_old(char **old, int to_free);
char		*take_slash_of(char *arg);

/*************************************************************** */
// SIMPLE WILD EXPAND :
/*************************************************************** */

char		**get_new_args(char **old, int new_len, t_dir_cont *dir_cont);
int			count_matches(char *old, t_dir_cont *dir_cont);
char		**wild_expand(char **old);
char		*wild_expand_red(char *old, int ref);
/**************************************************************/
// SEARCHING TOOLS :
/**************************************************************/
int			check_last(char *needl, char *haystak, int i);
int			check_midd(char *needle, char *haystack, int *start, int *index);
int			check_first(char *needle, char *haystak, int *start, int *index);
int			check_glob(char *val, t_globing *node);
int			check_node_for_valid(t_globing *wild, t_dir_cont *head,
				int fil_or_dir);

/********************************************************** */
// SOME WEIRD HANDLING:
/********************************************************** */
char		**check_empty_ones(char **old, char **as);

#endif
