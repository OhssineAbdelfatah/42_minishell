/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:34:09 by aohssine          #+#    #+#             */
/*   Updated: 2024/11/11 03:57:02 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		check_red(t_cmd_exec *p, int *ref, int *last_status);
void	reset_fds(t_cmd *cmd);

int		exec_builtin(t_cmd *cmd, int *last_status, int ref);
bool	is_builtin(t_cmd *cmd, int *status, int *last_status, int ref);

/*   ECHO   */
int		echo(t_new_cmd *cmd);

/*  CD  */
int		cd(t_cmd *cmd);

/*  PWD */
int		pwd(void);

/*  ENV  */
t_env	*init_env(char **env_main);
t_env	*creat_env(char *pair);
void	add_back_env(t_env **head, t_env *node);
int		print_env(t_env *env);

/*  EXPORT  */
int		export(t_cmd_exec *p);
void	print_export(t_env *env);
t_env	*env_exist(char *key, t_env *node);
t_env	*creat_new_env(char *key, char *value);
void	update_env(t_env *node, char *value);
char	*get_key(char *arg);
char	*get_value(char *arg);

/*  UNSET   */
void	destroy_single_env(t_env *node);
int		unset_env(t_env **head, char **key);
bool	is_valid(char *key);

/*   EXIT   */
int		exit_blt(t_new_cmd *arg);
void	error_exit(char *str);
void	check_plus_minus(char *str, int i, int sign);
/*  UTILS   */

char	**lstoarry(t_env *root);

#endif