/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 20:37:25 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/02 17:31:14 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

char	**ms_builtin_setenv(char **env)
{
	char		*cmd;

	if (ft_strcmp(g_cmd[0], "setenv") == 0)
		ms_del_cmd(0);
	if (!g_cmd || g_cmd[0][0] == '=')
	{
		ft_printf("env: setenv : Specify a value [NAME=VALUE]\n");
		g_cmd = ms_free_tab(g_cmd);
		return (env);
	}
	cmd = ft_strdup(g_cmd[0]);
	if (ft_cindex(g_cmd[0], '=') > 0)
		if (!env || ms_builtin_srchnrep(cmd, env) > 0)
			env = ms_builtin_addenv(g_cmd[0], env);
	free(cmd);
	ms_del_cmd(0);
	return (env);
}

int		ms_builtin_srchnrep(char *cmd, char **env)
{
	int		index;
	int		i;

	i = 0;
	index = ft_cindex(cmd, '=');
	while (env && env[i])
	{
		if (ft_strncmp(cmd, env[i], index) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(cmd);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ms_builtin_addenv(char *value, char **env)
{
	int		len;
	char	**nenv;

	len = 0;
	while (env && env[len])
		len++;
	nenv = NULL;
	if (!(nenv = (char**)malloc(sizeof(char*) * (len + 2))))
		return (NULL);
	nenv[len + 1] = NULL;
	len = 0;
	while (env && env[len])
	{
		nenv[len] = ft_strdup(env[len]);
		len++;
	}
	nenv[len] = ft_strdup(value);
	nenv[len + 1] = NULL;
	if (env)
		ft_tabdel(env);
	return (nenv);
}
