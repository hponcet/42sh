/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:45:06 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/24 17:10:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void		ms_search_exit(void)
{
	int		e;

	e = 0;
	ft_term_reset();
	if (g_curs.opt->htbl == 1)
		ft_hash_delhtbl(g_curs.hash_bin, __HTBL_LEN__);
	ft_hash_delhtbl(g_curs.alias, __HTBL_LEN__);
	if (g_cmd && g_cmd[0] && ft_strcmp(g_cmd[0], "exit") == 0 && g_cmd[1])
		e = atoi(g_cmd[1]);
	if (e >= 0 && e <= 255)
		exit(e);
	else
		exit(0);
}

char		**ms_search_builtin_env(char *cmd, char **env)
{
	if (ft_strcmp(g_cmd[0], "env") == 0)
	{
		g_moddedenv += 1;
		ms_builtin_env(cmd, env);
	}
	else if (ft_strcmp(g_cmd[0], "setenv") == 0)
	{
		if (g_moddedenv == 1)
			env = ms_builtin_setenv(env);
		else
			g_curs.env = ms_builtin_setenv(g_curs.env);
	}
	else if (ft_strcmp(g_cmd[0], "unsetenv") == 0)
	{
		if (g_moddedenv == 1)
			env = ms_builtin_unsetenv(env);
		else
			g_curs.env = ms_builtin_unsetenv(g_curs.env);
	}
	else if (ft_strcmp(g_cmd[0], "exit") == 0)
		ms_search_exit();
	return (env);
}

char		**ms_search_paths(void)
{
	char	**path;
	char	*joinpath;

	path = NULL;
	joinpath = NULL;
	if ((joinpath = ms_get_value(g_curs.env, "PATH")))
		path = ft_strsplit(joinpath, ':');
	else if (g_curs.opt->envpath == 1)
		path = ft_strsplit(__DEFAULT_PATH__, ':');
	ft_strdel(&joinpath);
	return (path);
}

char		*ms_search_bin(char **env)
{
	char	**path;
	char	*joinpath;
	char	*pathbin;

	path = NULL;
	pathbin = NULL;
	if (g_cmd && g_cmd[0] && g_cmd[0][0] == '/' && access(g_cmd[0], X_OK) > -1)
		return (ft_strdup(g_cmd[0]));
	if ((g_curs.opt->htbl) && (pathbin = ft_hash_search(g_curs.hash_bin,
					g_cmd[0], __HTBL_LEN__)))
		return (pathbin);
	if ((joinpath = ms_get_value(env, "PATH")))
		path = ft_strsplit(joinpath, ':');
	else if ((g_curs.opt->envpath))
		path = ft_strsplit(__DEFAULT_PATH__, ':');
	pathbin = ms_search_pathbin(path, env);
	if (!pathbin)
	{
		ft_printf("21sh: Command not found: %s\n", g_cmd[0]);
		ft_tabdel(g_cmd);
		g_cmd = NULL;
	}
	ft_strdel(&joinpath);
	free(path);
	return (pathbin);
}

char		*ms_search_pathbin(char **path, char **env)
{
	char	*tmp;
	char	*pathbin;
	int		i;

	i = 0;
	if (!path && !g_curs.opt->envpath)
		return (NULL);
	else if (!path)
		path = ms_get_path(env);
	pathbin = NULL;
	while (path && path[i])
	{
		tmp = path[i];
		pathbin = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = pathbin;
		pathbin = ft_strjoin(tmp, g_cmd[0]);
		free(tmp);
		if (access(pathbin, X_OK) > -1)
			return (pathbin);
		i++;
		ft_strdel(&pathbin);
	}
	return (NULL);
}
