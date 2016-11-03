/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_getinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:01:19 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 18:54:16 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_compl		*ft_compl_makefile(struct dirent *s_dir, char *path)
{
	t_compl			*file;
	struct stat		s_stat;
	char			*tmp;

	file = (t_compl*)malloc(sizeof(t_compl));
	if (!file)
		return (NULL);
	file->name = ft_strdup(s_dir->d_name);
	tmp = ft_joinf("%s/%s", path, file->name);
	lstat(tmp, &s_stat);
	if (S_ISDIR(s_stat.st_mode))
		file->type = 1;
	else
		file->type = 0;
	file->prev = file;
	file->next = file;
	file->id = 0;
	ft_strdel(&tmp);
	return (file);
}

t_compl		*ft_compl_makechain(char *path, t_compl *ret, char *find)
{
	DIR				*dirp;
	struct dirent	*s_dir;
	t_compl			*file;

	if ((dirp = opendir(path)) == NULL)
		return (NULL);
	while ((s_dir = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(s_dir->d_name, "..") == 0 || ft_strcmp(s_dir->d_name, ".")
				== 0)
			continue ;
		if (!find || ft_strncmp(s_dir->d_name, find, ft_strlen(find)) == 0)
		{
			file = ft_compl_makefile(s_dir, path);
			ft_compl_sortchain(&ret, file);
		}
	}
	closedir(dirp);
	return (ret);
}

void		ft_compl_sortchain(t_compl **list, t_compl *file)
{
	t_compl	*tmp;

	tmp = list[0];
	if (!tmp)
	{
		*list = file;
		file->id = 1;
		return ;
	}
	if (tmp == tmp->next)
	{
		file->next = tmp;
		file->prev = tmp;
		tmp->prev = file;
		tmp->next = file;
		file->id = 2;
		return ;
	}
	while (tmp->id < tmp->next->id)
		tmp = tmp->next;
	tmp->next->prev = file;
	file->next = tmp->next;
	tmp->next = file;
	file->prev = tmp;
	file->id = tmp->id + 1;
}

char		*ft_compl_getfind(char *str)
{
	int		i;
	int		j;
	char	*find;

	find = NULL;
	i = ft_strlen(str) - 1;
	j = i;
	if (str[i] == ' ')
		return (NULL);
	while (i >= 0 && str[i] != ' ')
		i--;
	i++;
	if (str[i - 1] == ' ')
		find = ft_strsub(str, i, j - i + 1);
	return (find);
}
