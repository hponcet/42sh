/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:25:03 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/21 18:42:39 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	glob_count_quote_rev(char *s, int i, char c)
{
	int		j;

	j = 1;
	i--;
	while (s[i] != c && s[i])
	{
		i--;
		j++;
	}
	return (j);
}

int			glob_check(char *str)
{
	int		len;

	if (!str)
		return (0);
	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		if ((str[len] == '['
				|| (str[len] == '?' && len > 0 && str[len - 1] != '$')
				|| str[len] == '*' || str[len] == '{') && len > 0
				&& str[len - 1] != '\\')
			return (1);
		if (str[len] == '\"' || str[len] == '\'' || str[len] == 96)
			len -= glob_count_quote_rev(str, len, str[len]);
		len--;
	}
	return (0);
}

static char	*glob_nomatch(char *nm)
{
	ft_putstr_fd("21sh: no matches found: ", STDERR_FILENO);
	ft_putendl_fd(nm, STDERR_FILENO);
	return (NULL);
}

char		*ft_glob(char *tabl)
{
	int		i;
	char	**cmd;
	char	*find;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = NULL;
	tmp = NULL;
	cmd = ft_strsplit(tabl, ' ');
	while (cmd[i])
	{
		find = ft_strdup(cmd[i]);
		if (ft_glob_check(cmd[i]) && (tmp = ft_glob_replace(cmd[i])))
			ret = ft_joinf("%xs %s", ret, tmp);
		else if (ft_glob_check(cmd[i]) && !tmp)
			return (ft_glob_nomatch(cmd, NULL, find));
		else
			ret = ft_joinf("%xs %s", ret, cmd[i]);
		ft_strdel(&tmp);
		ft_strdel(&find);
		i++;
	}
	free_tab(cmd);
	return (ret);
}

int			glob_compare(char *s1, char *s2)
{
	if ((!*s1 && !*s2))
		return (1);
	else if (*s1 == '?' && *s2)
		return (glob_compare(s1 + 1, s2 + 1));
	else if (*s1 == '*' && s1[1] == '*')
		return (glob_compare(s1 + 1, s2));
	else if (*s1 == '*' && *s2 == s1[1])
		return (glob_compare(s1 + 1, s2) || glob_compare(s1, s2 + 1));
	else if (*s1 == '*' && *s2 != s1[1] && *s2)
		return (glob_compare(s1, s2 + 1));
	else if (*s1 == '\\' && (s1[1] == '*'
				|| s1[1] == '?' || s1[1] == '{'
				|| s1[1] == '[') && *s2 == s1[1])
		return (glob_compare(s1 + 2, s2 + 1));
	else if (*s1 == *s2)
		return (glob_compare(s1 + 1, s2 + 1));
	return (0);
}
