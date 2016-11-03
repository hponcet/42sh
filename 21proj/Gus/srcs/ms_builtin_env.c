/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 12:38:07 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/24 16:21:39 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

static char	**ret_nenv(char **env)
{
	char	**nenv;

	nenv = ms_get_env(env);
	if (g_cmd[0][0] == '-')
		g_cmd[0] = ft_strcut(g_cmd[0], 1);
	while (g_cmd && (ft_cindex(g_cmd[0], '=') > -1 ||
				g_cmd[0][0] == 'i' || g_cmd[0][0] == 'u'))
	{
		if (g_cmd[0][0] == 'i' || g_cmd[0][0] == 'u')
			nenv = ms_builtin_env_opt(nenv);
		if (g_cmd && ft_cindex(g_cmd[0], '=') > -1)
			nenv = ms_builtin_setenv(nenv);
	}
	return (nenv);
}

static char	**exec_nenv(char *cmd, char **nenv)
{
	g_curs.error = 0;
	if (ft_strncmp(g_cmd[0], "env", 3) == 0 ||
			ft_strncmp(g_cmd[0], "cd", 2) == 0)
		nenv = ms_search_builtin_env(cmd, nenv);
	else if (g_cmd && nenv)
	{
		ms_exec_fork(NULL, nenv);
		ms_del_cmd(0);
	}
	return (nenv);
}

void		ms_builtin_env(char *cmd, char **env)
{
	char		**nenv;

	cmd = NULL;
	nenv = NULL;
	ms_del_cmd(0);
	while (g_cmd && ft_strcmp(g_cmd[0], "env") == 0)
		ms_del_cmd(0);
	if (!g_cmd)
	{
		ms_print_env(env);
		return ;
	}
	if (g_cmd[0][0] == '-' || ft_cindex(g_cmd[0], '=') > -1)
		nenv = ret_nenv(env);
	if (g_cmd && (nenv || g_curs.error == 1))
		nenv = exec_nenv(cmd, nenv);
	else if (!g_cmd && (nenv || g_curs.error == 1))
	{
		g_curs.error = 0;
		ms_print_env(nenv);
	}
	else if (!g_cmd && !nenv)
		ms_print_env(env);
	if (nenv)
		ft_tabdel(nenv);
}

char		**ms_builtin_env_opt(char **env)
{
	if (g_cmd[0][0] == 'i')
	{
		if (g_cmd[0][1] != '\0')
			g_cmd[0] = ft_strcut(g_cmd[0], 1);
		else
		{
			if (!g_cmd[1])
				g_cmd = ms_free_tab(g_cmd);
			else
				ms_del_cmd(0);
			env = ms_free_tab(env);
		}
		g_i = 1;
		g_curs.error = 1;
	}
	else if (env && g_cmd[0][0] == 'u')
		env = ms_builtin_env_opt_u(env);
	else
	{
		ft_printf("21sh: env: illegal option -- %c\n", g_cmd[0][0]);
		ft_printf(" usage: env [-i] [-u name] [name=value ...]\n");
		g_cmd = ms_free_tab(g_cmd);
		env = ms_free_tab(env);
	}
	return (env);
}

char		**ms_builtin_env_opt_u(char **env)
{
	if (!env)
		return (NULL);
	if (g_cmd[0][1] != '\0')
	{
		g_cmd[0] = ft_strcut(g_cmd[0], 1);
		env = ms_builtin_unsetenv(env);
	}
	else
	{
		if (!g_cmd[1])
		{
			ft_printf("21sh: env: illegal option -- u\n");
			ft_printf(" usage: env [-i] [-u name] [name=value ...]\n");
			env = ms_free_tab(env);
			g_cmd = ms_free_tab(g_cmd);
			return (env);
		}
		ms_del_cmd(0);
		env = ms_builtin_unsetenv(env);
	}
	return (env);
}
