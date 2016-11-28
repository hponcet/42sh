/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursh_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:16:51 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/28 16:38:36 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		ft_cindex_from(char *str, char c, int i)
{
	if (i < 0)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int		ft_cindex_rev_from(char *str, char c, int i)
{
	if (i < 0)
		return (-1);
	while (i >= 0 && str[i])
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (-1);
}

void			ft_cursh_proc(char **str, int s, int e)
{
	char	*joined;
	char	**test;
	char	*tmp;
	char	*start;
	int		i;

	i = 0;
	start = ft_strsub(str[0], 0, s);
	joined = ft_strsub(str[0], s + 1, e - s - 1);
	test = ft_strsplit(joined, ',');
	ft_strdel(&joined);
	joined = ft_strdup(str[0] + e + 1);
	while (test[i])
	{
		tmp = ft_strdup(test[i]);
		free(test[i]);
		test[i] = ft_joinf("%s%xs", start, tmp);
		i++;
	}
	i = -1;
	ft_strdel(&start);
	free(str[0]);
	str[0] = ft_strnew(0);
	while (test[++i])
		str[0] = ft_joinf("%xs %s", str[0], test[i]);
	str[0] = ft_joinf("%xs %s", str[0], joined);
	ft_strdel(&joined);
	free_tab(test);
}

void			ft_cursh_replace(char **str)
{
	int		oc;
	int		cc;

	oc = ft_cindex_rev(str[0], '{');
	cc = ft_cindex(str[0], '}');
	while (cc >= 0 && cc <= (int)ft_strlen(str[0]))
	{
		if (oc < 0)
		{
			oc = ft_cindex_rev(str[0], '{');
			cc = ft_cindex_from(str[0], '}', cc + 1);
		}
		if (cc - oc > 0 && ft_cindex_rev_from(str[0], ',', cc) > oc)
		{
			ft_cursh_proc(str, oc, cc);
			break ;
		}
		oc = ft_cindex_rev_from(str[0], '{', oc - 1);
	}
}
