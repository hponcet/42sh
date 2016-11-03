/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 00:16:02 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/18 00:31:06 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MINISHELL_H
# define MS_MINISHELL_H
# include "../libft/includes/libft.h"
# include "ft_config.h"
# include "ft_21sh.h"
# include <sys/param.h>
# include <sys/types.h>
# include <sys/wait.h>

char				**g_cmd;
int					g_moddedenv;
int					g_i;

/*
** main.c
*/
void				ft_cmd(char *cmd);
char				**ft_cmd_split(char *s);

/*
** ms_get_cmd.c
*/
int					ms_get_nbc(char *buf);
int					ft_cmd_count_quote(char *s, int i, char c);
char				**ms_parse_cmd(char *buf);
char				**ms_get_cmd(char *buf);
char				**ms_free_tab(char **teub);
void				ms_del_cmd(int l);

/*
** ms_exec.c
*/
void				ms_exec(char *cmd, char **env);
void				ms_exec_bin(char *path, char **env);
char				*ms_search_bin(char **env);
char				**ms_search_paths(void);
void				ms_search_exit(void);
char				*ms_search_pathbin(char **path, char **env);
char				**ms_search_builtin_env(char *cmd, char **env);
void				ms_exec_fork(char *cmd, char **env);

/*
** ms_builtin_setenv.c
*/
char				**ms_builtin_setenv(char **env);
char				**ms_builtin_addenv(char *value, char **env);
int					ms_builtin_srchnrep(char *cmd, char **env);

/*
** ms_builtin_unsetenv.c
*/
char				**ms_builtin_unsetenv(char **env);
char				**ms_builtin_delenv(char **env);
char				**ms_builtin_srchndel(int j, char **env);

/*
** ms_builtin_env.c
*/
void				ms_builtin_env(char *cmd, char **env);
char				**ms_builtin_env_opt(char **env);
char				**ms_builtin_env_opt_u(char **env);
/*
** ms_builtin_cd.c
*/
char				**ms_builtin_cd(char **env);
int					ms_builtin_cd_tild(char **env);
char				**ms_builtin_cd_home(char **env);
char				**ms_builtin_cd_absolute_path(char **env);
char				**ms_builtin_cd_minus(char **env);

/*
** ms_get.c
*/
char				**ms_get_path(char **env);
char				*ms_get_value(char **env, char *name);
char				**ms_get_env(char **env);
void				ms_print_env(char **env);
int					ms_get_point(void);

#endif
