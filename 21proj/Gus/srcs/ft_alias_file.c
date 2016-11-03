/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 18:16:32 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/24 19:08:30 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*ft_alias_delquotes(char *str)
{
	char	*ret;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	j = 0;
	ret = ft_strnew(i);
	i = 0;
	while (str[j])
	{
		if (str[j] == '"')
		{
			j++;
			continue ;
		}
		ret[i] = str[j];
		i++;
		j++;
	}
	return (ret);
}

void	ft_alias_htbltofile(void)
{
	t_hash	**tmp;
	int		i;
	int		fd;
	char	*aliaspath;

	i = 0;
	tmp = g_curs.alias;
	aliaspath = ft_strjoin(getenv("HOME"), "/.21shrc");
	fd = open(aliaspath, O_TRUNC | O_WRONLY, 0644);
	while (i < __HTBL_LEN__)
	{
		while (tmp[i])
		{
			ft_putstr_fd("alias ", fd);
			ft_putstr_fd(tmp[i]->name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp[i]->value, fd);
			ft_putendl_fd("\"", fd);
			tmp[i] = tmp[i]->next;
		}
		i++;
	}
	ft_strdel(&aliaspath);
	close(fd);
	tmp = NULL;
}

void	ft_alias_htbladd(char *buf)
{
	char	**tb;
	char	*tmp;
	char	*tmp2;

	tb = ft_strsplit(buf, '=');
	tmp = ft_alias_delquotes(tb[1]);
	if (ft_strncmp(tb[0], "alias ", 6) == 0)
		tmp2 = ft_strsub(tb[0], 6, ft_strlen(tb[0]) - 6);
	else
		tmp2 = ft_strdup(tb[0]);
	ft_hash_add(g_curs.alias, tmp2, tmp, __HTBL_LEN__);
	ft_tabdel(tb);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	tb = NULL;
}

void	ft_alias_gethtbl(void)
{
	int		fd;
	char	*aliaspath;
	char	*buf;

	buf = NULL;
	if (g_curs.alias)
	{
		ft_hash_delhtbl(g_curs.alias, __HTBL_LEN__);
		g_curs.alias = NULL;
	}
	if (!g_curs.alias)
		g_curs.alias = ft_hash_newtbl(__HTBL_LEN__);
	aliaspath = ft_strjoin(getenv("HOME"), "/.21shrc");
	if ((fd = open(aliaspath, O_RDONLY, 0644)) == -1)
		fd = open(aliaspath, O_CREAT | O_RDONLY, 0644);
	while (get_next_line(fd, &buf) > 0)
	{
		if (ft_strncmp(buf, "alias", 5) == 0 && ft_cindex(buf, '=') > 0)
			ft_alias_htbladd(buf);
		ft_strdel(&buf);
	}
	ft_strdel(&aliaspath);
	close(fd);
}
