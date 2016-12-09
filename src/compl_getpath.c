/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_getpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 14:37:08 by hponcet           #+#    #+#             */
/*   Updated: 2016/12/09 20:33:52 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	getroot(char **ret)
{
	int		len;
	char	*tmp;

	if (ret[1][1])
	{
		len = ft_strlen(ret[1]) - 1;
		tmp = ft_strsub(ret[1], 1, len);
		free(ret[1]);
		ret[1] = tmp;
		ret[0] = ft_strdup("/");
	}
	else
	{
		ft_strdel(&ret[1]);
		ret[0] = ft_strdup("/");
	}
}

static void	getpathroot(char **ret)
{
	int		i;
	char	*tmp;

	i = ft_cindex_rev(ret[1], '/');
	if (ret[1][i + 1])
	{
		tmp = ft_strsub(ret[1], i + 1, ft_strlen(ret[1]) - i);
		ret[0] = ft_strsub(ret[1], 0, i + 1);
		free(ret[1]);
		ret[1] = tmp;
	}
	else
	{
		ret[0] = ft_strdup(ret[1]);
		free(ret[1]);
		ret[1] = ft_strnew(0);
	}
}

static void	getpath(char **ret, char *pwd)
{
	int		i;
	char	*path;
	char	*find;

	i = ft_cindex_rev(ret[1], '/');
	find = ft_strsub(ret[1], i + 1, ft_strlen(ret[1]) - i);
	path = ft_strsub(ret[1], 0, i + 1);
	ret[0] = ft_joinf("%s/%s", pwd, path);
	ft_strdel(&path);
	free(ret[1]);
	ret[1] = find;
}

static void	gethomepath(t_shell *shell, char **cmd)
{
	t_env	*homeenv;
	char	*tmp;
	char	*homepath;
	char	*find;
	int		i;

	if (!(homeenv = get_env_ptr(shell->env_lst, "HOME")))
		homepath = ft_strdup("/Users/");
	else
		homepath = ft_strdup(homeenv->val);
	i = ft_cindex_rev(cmd[1], '/');
	find = ft_strsub(cmd[1], i + 1, ft_strlen(cmd[1]) - i);
	tmp = ft_strsub(cmd[1], 1, i);
	free(cmd[1]);
	cmd[0] = ft_joinf("%s%s", homepath, tmp);
	cmd[1] = find;
	ft_strdel(&tmp);
	ft_strdel(&homepath);
}

void		compl_getpath(t_shell *shell, char **ret)
{
	int		i;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, MAXPATHLEN);
	if (!ret[1])
	{
		ret[1] = ft_strnew(0);
		ret[0] = ft_strdup(pwd);
		ft_strdel(&pwd);
		return ;
	}
	i = ft_cindex_rev(ret[1], '/');
	if (ret[1][0] == '~' && ret[1][1] == '/')
		gethomepath(shell, ret);
	else if (i == 0)
		getroot(ret);
	else if (ret[1][0] == '/' && i > 0)
		getpathroot(ret);
	else if (ret[1][0] != '/' && i > 0)
		getpath(ret, pwd);
	else
		ret[0] = ft_strdup(pwd);
	ft_strdel(&pwd);
}

char		**compl_pathbin(t_shell *shell)
{
	t_env	*pathbin;
	char	**path;
	char	*joinpath;

	path = NULL;
	joinpath = NULL;
	if (!(pathbin = get_env_ptr(shell->env_lst, "PATH")))
	{
		ft_put_error(ER_PATH, 0);
		return (NULL);
	}
	if ((joinpath = ft_strdup(pathbin->val)))
		path = ft_strsplit(joinpath, ':');
	ft_strdel(&joinpath);
	return (path);
}
