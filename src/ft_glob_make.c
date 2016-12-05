/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 22:12:13 by hponcet           #+#    #+#             */
/*   Updated: 2016/12/05 16:33:47 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_glob_replace(char *cmd)
{
	char	**cmd_decomp;
	t_glob	*pathlist;
	t_glob	*tmp;
	char	*tmp2;
	char	*ret;

	cmd_decomp = ft_glob_make_pathfind(cmd);
	ft_glob_path(cmd_decomp);
	pathlist = ft_glob_pathtree(cmd_decomp[2]);
	tmp = pathlist;
	if (!tmp)
		return (NULL);
	ret = ft_strnew(0);
	while (tmp)
	{
		tmp2 = ft_glob_makestr(tmp->path, cmd_decomp[1], tmp->path);
		if (tmp2)
			ret = ft_joinf("%s %s", ret, tmp2);
		tmp = tmp->next;
	}
	ft_glob_delchain(pathlist);
	ft_strdel(&cmd_decomp[0]); // path
	ft_strdel(&cmd_decomp[1]); // find
	ft_strdel(&cmd_decomp[2]); // absolute path
	free(cmd_decomp);
	cmd_decomp = NULL;
	return (ret);
}

t_glob	*ft_glob_makefile(struct dirent *s_dir, char *path)
{
	t_glob			*file;

	file = (t_glob*)malloc(sizeof(t_glob));
	if (!file)
		return (NULL);
	file->name = ft_strdup(s_dir->d_name);
	file->path = ft_strjoin(path, file->name);
	file->next = NULL;
	return (file);
}

char	*ft_glob_tglobtostr(t_glob *lst)
{
	char	*ret;
	t_glob	*list;

	list = lst;
	ret = NULL;
	if (!lst)
		return (NULL);
	while (list)
	{
		if (!ret)
		{
			ret = ft_strdup(list->path);
			list = list->next;
			continue ;
		}
		ret = ft_joinf("%xs %s", ret, list->path);
		list = list->next;
	}
	return (ret);
}

void	ft_glob_delchain(t_glob *chain)
{
	t_glob	*tmp;
	t_glob	*prev;

	tmp = chain;
	while (tmp)
	{
		prev = tmp;
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->path);
		tmp = tmp->next;
		free(prev);
		prev = NULL;
	}
}

char	*ft_glob_makestr(char *path, char *find, char *absolute)
{
	DIR				*dirp;
	struct dirent	*s_dir;
	t_glob			*file;
	t_glob			*ret;
	char			*str;

	ret = NULL;
	if ((dirp = opendir(absolute)) == NULL)
		return (NULL);
	while ((s_dir = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(s_dir->d_name, "..") == 0 || ft_strcmp(s_dir->d_name, ".") == 0
				|| (ft_strncmp(s_dir->d_name, ".", 1) == 0 && find[0] != '.'))
			continue ;
		if (ft_glob_compare(find, s_dir->d_name) != 0
				&& (file = ft_glob_makefile(s_dir, path)))
			ft_glob_sortchain(&ret, file);
	}
	closedir(dirp);
	if (!ret)
		return (NULL);
	str = ft_glob_tglobtostr(ret);
	ft_glob_delchain(ret);
	return (str);
}
