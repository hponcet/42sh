/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 15:36:51 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/26 14:44:47 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_compl_wis(char *str)
{
	int		i;
	int		j;

	if (!str)
		return (0);
	i = ft_strlen(str) - 1;
	j = 0;
	while (str[j] && (str[j] == ' ' || str[j] == '	'))
		j++;
	if (i == j)
		return (0);
	while (i >= j)
	{
		if (str[i] == ' ' && i > 0 && str[i - 1] != ' ' && str[i - 1] != ';'
				&& str[i - 1] != '`')
			return (1);
		if (str[i] == ';' || str[i] == '`')
			return (0);
		i--;
	}
	return (0);
}

void		ft_compl_delchain(t_compl *chain)
{
	t_compl	*tmp;

	chain = chain->prev;
	while (chain && chain->id != 1)
	{
		tmp = chain;
		chain->type = 0;
		chain->len = 0;
		chain->id = 0;
		ft_strdel(&chain->name);
		chain->next = NULL;
		chain = chain->prev;
		free(tmp);
	}
	if (!chain)
		return ;
	chain->type = 0;
	chain->len = 0;
	chain->id = 0;
	ft_strdel(&(chain->name));
	chain->next = NULL;
	free(chain);
}

void		ft_compl_file(char *str)
{
	char	**ret;
	t_compl	*dir;

	dir = NULL;
	ret = (char**)malloc(sizeof(char*) * 3);
	ret[2] = NULL;
	ret[1] = ft_compl_getfind(str);
	ft_compl_getpath(ret);
	dir = ft_compl_makechain(ret[0], dir, ret[1]);
	if (!ret[1])
		ret[1] = ft_strdup("");
	if (dir)
		ft_compl_display(dir, ret[1]);
	ft_strdel(&ret[0]);
	ft_strdel(&ret[1]);
	free(ret);
}

void		ft_compl_bin(char *str)
{
	char	**path;
	char	*find;
	t_compl	*dir;
	int		i;

	dir = NULL;
	path = ms_search_paths();
	if (!path)
		return ;
	find = ft_strdup(str);
	i = 0;
	while (path && path[i])
	{
		ft_signal();
		dir = ft_compl_makechain(path[i], dir, find);
		i++;
	}
	ft_tabdel(path);
	if (dir)
		ft_compl_display(dir, find);
	ft_strdel(&find);
}

char		*ft_compl(char *str)
{
	if (ft_compl_wis(str) == 1)
		ft_compl_file(str);
	else
	{
		if (!str)
			return (str);
		else
			ft_compl_bin(str);
	}
	return (str);
}
