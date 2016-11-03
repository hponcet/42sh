/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:36:08 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/24 16:23:56 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

char	**ms_builtin_cd(char **env)
{
	if (ft_strcmp(g_cmd[0], "cd") != 0)
		return (env);
	ms_del_cmd(0);
	if (g_cmd && g_cmd[0][0] == '~')
		if (ms_builtin_cd_tild(env) < 1)
			return (env);
	if (!g_cmd)
		env = ms_builtin_cd_home(env);
	else if (g_cmd[0][0] == '-')
	{
		if (g_cmd[0][1] != '\0')
			ft_putendl("21sh: cd: option not implemented.");
		else
			env = ms_builtin_cd_minus(env);
	}
	else
		env = ms_builtin_cd_absolute_path(env);
	g_cmd = ms_free_tab(g_cmd);
	return (env);
}

char	**ms_builtin_cd_minus(char **env)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	tmp = ms_get_value(env, "OLDPWD");
	if (!tmp || tmp[0] == '\0')
		ft_putendl("21sh: cd: Environnement variable OLDPWD not set.");
	else if (chdir(tmp) < 0)
		ft_printf("21sh: cd: no such directory: %s\n", tmp);
	else
	{
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		tmp = ms_get_value(env, "PWD");
		oldpwd = ft_strjoin("OLDPWD=", tmp);
		if (ms_builtin_srchnrep(pwd, env) > 0)
			env = ms_builtin_addenv(pwd, env);
		if (ms_builtin_srchnrep(oldpwd, env) > 0)
			env = ms_builtin_addenv(oldpwd, env);
		ft_strdel(&pwd);
		ft_strdel(&oldpwd);
	}
	free(tmp);
	return (env);
}

int		ms_builtin_cd_tild(char **env)
{
	char	*tmp;
	char	*tmp2;

	tmp = ms_get_value(env, "HOME");
	if (!tmp)
	{
		ft_putendl("21sh: cd: Environnement variable HOME not set.");
		g_cmd = ms_free_tab(g_cmd);
		return (0);
	}
	tmp2 = ft_strjoin(tmp, g_cmd[0] + 1);
	free(tmp);
	free(g_cmd[0]);
	g_cmd[0] = tmp2;
	return (1);
}

char	**ms_builtin_cd_home(char **env)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	tmp = ms_get_value(env, "HOME");
	if (!tmp)
		ft_putendl("21sh: cd: Environnement variable HOME not set.");
	else if (chdir(tmp) < 0)
		ft_printf("21sh: cd: no such directory: %s\n", tmp);
	else
	{
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		tmp = ms_get_value(env, "PWD");
		oldpwd = ft_strjoin("OLDPWD=", tmp);
		if (ms_builtin_srchnrep(pwd, env) > 0)
			env = ms_builtin_addenv(pwd, env);
		if (ms_builtin_srchnrep(oldpwd, env) > 0)
			env = ms_builtin_addenv(oldpwd, env);
		ft_strdel(&oldpwd);
		ft_strdel(&pwd);
	}
	free(tmp);
	return (env);
}

char	**ms_builtin_cd_absolute_path(char **env)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(tmp, MAXPATHLEN);
	oldpwd = ft_strjoin("OLDPWD=", tmp);
	ft_strdel(&tmp);
	if (chdir(g_cmd[0]) < 0)
	{
		ft_printf("21sh: cd: no such directory: %s\n", g_cmd[0]);
		free(oldpwd);
		return (env);
	}
	tmp = getcwd(tmp, MAXPATHLEN);
	pwd = ft_strjoin("PWD=", tmp);
	if (ms_builtin_srchnrep(pwd, env) > 0)
		env = ms_builtin_addenv(pwd, env);
	if (ms_builtin_srchnrep(oldpwd, env) > 0)
		env = ms_builtin_addenv(oldpwd, env);
	g_curs.env = env;
	ft_strdel(&tmp);
	ft_strdel(&oldpwd);
	ft_strdel(&pwd);
	return (env);
}
