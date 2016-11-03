/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 13:48:10 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/19 15:43:23 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

char		*ms_get_value(char **env, char *name)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = ft_strlen(name);
	ret = NULL;
	while (env && env[j])
	{
		if (ft_strncmp(name, env[j], i) == 0 && env[j][i] == '=')
		{
			ret = ft_strdup(env[j] + i + 1);
			return (ret);
		}
		j++;
	}
	return (NULL);
}

char		**ms_get_path(char **env)
{
	int		j;
	char	**ret;

	j = 0;
	ret = NULL;
	if (env && env[j])
	{
		while (!(ft_strncmp("PATH", env[j], 4) == 0 && env[j][4] == '='))
			j++;
		if (env[j] && ft_strncmp("PATH", env[j], 4) == 0 && env[j][4] == '=')
			ret = ft_strsplit(env[j] + 5, ':');
	}
	return (ret);
}

char		**ms_get_env(char **env)
{
	char	**renv;
	int		i;

	renv = NULL;
	i = 0;
	if (!env)
		return (renv);
	while (env[i])
		i++;
	if (!(renv = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	renv[i] = NULL;
	i = 0;
	while (env[i])
	{
		renv[i] = ft_strdup(env[i]);
		i++;
	}
	return (renv);
}

void		ms_print_env(char **env)
{
	int		i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

int			ms_get_point(void)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp = getcwd(tmp, MAXPATHLEN);
	if (!tmp)
	{
		ft_putendl("ms: cd: Environnement variable PWD not set.");
		g_cmd = ms_free_tab(g_cmd);
		return (0);
	}
	tmp2 = ft_strjoin(tmp, g_cmd[0] + 1);
	free(tmp);
	free(g_cmd[0]);
	g_cmd[0] = tmp2;
	return (1);
}
