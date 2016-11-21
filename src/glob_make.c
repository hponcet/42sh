/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_make.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 22:12:13 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/21 04:18:22 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*glob_replace(t_shell *shell, char *cmd)
{
	char	**pth_cmd;
	char	*ret;

	pth_cmd = (char**)malloc(sizeof(char*) * 4);
	pth_cmd[3] = NULL;
	pth_cmd[2] = NULL;
	pth_cmd[0] = NULL;
	pth_cmd[1] = ft_strdup(cmd);
	glob_path(shell, pth_cmd);
	ret = glob_makestr(pth_cmd[0], pth_cmd[1], pth_cmd[2]);
	ft_strdel(&pth_cmd[0]);
	ft_strdel(&pth_cmd[1]);
	ft_strdel(&pth_cmd[2]);
	free(pth_cmd);
	pth_cmd = NULL;
	return (ret);
}

t_glob	*glob_makefile(struct dirent *s_dir, char *path)
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

char	*glob_tglobtostr(t_glob *lst)
{
	char	*ret;
	t_glob	*list;

	list = lst;
	ret = NULL;
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

void	glob_delchain(t_glob *chain)
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

char	*glob_makestr(char *path, char *find, char *absolute)
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
		if (ft_strcmp(s_dir->d_name, "..") == 0
				|| (ft_strncmp(s_dir->d_name, ".", 1) == 0 && find[0] != '.'))
			continue ;
		if (glob_compare(find, s_dir->d_name) != 0
				&& (file = glob_makefile(s_dir, path)))
			glob_sortchain(&ret, file);
	}
	closedir(dirp);
	if (!ret)
		return (NULL);
	str = glob_tglobtostr(ret);
	glob_delchain(ret);
	return (str);
}
