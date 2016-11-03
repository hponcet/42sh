/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 20:36:43 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/02 16:06:14 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

char	**ms_builtin_unsetenv(char **env)
{
	if (ft_strcmp(g_cmd[0], "unsetenv") == 0)
		ms_del_cmd(0);
	if (!g_cmd)
	{
		ft_printf("env: unsetenv : Specify a variable\n");
		g_cmd = ms_free_tab(g_cmd);
		return (env);
	}
	env = ms_builtin_delenv(env);
	return (env);
}

char	**ms_builtin_delenv(char **env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	if (!env || !env[0])
	{
		ms_del_cmd(0);
		return (NULL);
	}
	while (env[i])
	{
		if (ft_strncmp(g_cmd[0], env[i], ft_strlen(g_cmd[0])) == 0
		&& (env[i][ft_strlen(g_cmd[0])] == '='))
		{
			env = ms_builtin_srchndel(i, env);
			ms_del_cmd(0);
			return (env);
		}
		i++;
	}
	ms_del_cmd(0);
	return (env);
}

char	**ms_builtin_srchndel(int j, char **env)
{
	int		len;
	char	**nenv;
	int		i;

	i = 0;
	len = 0;
	nenv = NULL;
	while (env[i])
		i++;
	nenv = (char**)malloc(sizeof(char*) * i);
	nenv[i - 1] = NULL;
	if (i == 1)
		return (nenv);
	i = -1;
	while (env[len])
	{
		if (len == j)
			len++;
		nenv[++i] = ft_strdup(env[len]);
		len++;
		if (len == j)
			len++;
	}
	ft_tabdel(g_curs.env);
	return (nenv);
}
