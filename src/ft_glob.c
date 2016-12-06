/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:19:23 by hponcet           #+#    #+#             */
/*   Updated: 2016/12/06 17:27:41 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_glob_count_quote_rev(char *s, int i, char c)
{
	int		j;

	j = 1;
	i--;
	while (i >= 0 && s[i] && s[i] != c)
	{
		i--;
		j++;
	}
	return (j);
}

int			ft_glob_check(char *str)
{
	int		len;

	if (!str)
		return (0);
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		if (len > 0 && (str[len - 1] == '\\'
					|| (str[len] == '?' && str[len - 1] == '$')))
		{
			len -= 2;
			continue ;
		}
		if (str[len] == '[' || str[len] == '?' || str[len] == '*')
			return (1);
		if (str[len] == '\"' || str[len] == '\'' || str[len] == 96)
			len -= ft_glob_count_quote_rev(str, len, str[len]);
		len--;
	}
	return (0);
}

int			ft_glob_nomatch(char *nm, char *ret, char **tabl, char ** cmd)
{
	ft_putstr_fd("42sh: no matches found: ", STDERR_FILENO);
	ft_putendl_fd(nm, STDERR_FILENO);
	free_tab(cmd);
	ft_strdel(&nm);
	ft_strdel(&ret);
	free(tabl[0]);
	tabl[0] = ft_strdup(" ");
	return (1);
}

int			ft_glob(char **tabl)
{
	int		i;
	char	**cmd;
	char	*find;
	char	*ret;
	char	*tmp;

	i = -1;
	ret = ft_strnew(0);
	tmp = NULL;
	cmd = ft_strsplit(tabl[0], ' ');
	while (cmd[++i])
	{
		find = ft_strdup(cmd[i]);
		if (ft_glob_check(cmd[i]) == 1 && (tmp = ft_glob_replace(cmd[i])) && tmp[0])
			ret = ft_joinf("%xs %s", ret, tmp);
		else if (ft_glob_check(cmd[i]) == 1 && (!tmp || !tmp[0]))
			return (ft_glob_nomatch(find, ret, tabl, cmd));
		else
			ret = ft_joinf("%xs %s", ret, cmd[i]);
		ft_strdel(&tmp);
		ft_strdel(&find);
	}
	free_tab(cmd);
	free(tabl[0]);
	tabl[0] = ret;
	return (0);
}
