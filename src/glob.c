/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 16:25:03 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/21 06:07:54 by hponcet          ###   ########.fr       */
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

char		**ft_glob(t_shell *shell, char **t)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tamp;
	char	**ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (t[i])
	{
		if (glob_check(t[i]) == 1)
		{
			ft_putendl("yoyoyo");
			tmp = glob_func(shell, t[i]);
			tamp = join_tab_to_tab(ret, tmp);
			free_tab(ret);
			ret = tab_copy(tamp);
			free_tab(tmp);
			free_tab(tamp);
		}
		else
		{
			tamp = join_str_to_tab(ret, t[i]);
			free_tab(ret);
			ret = tamp;
		}
		i++;
	}
	return (ret);
}

char		**glob_func(t_shell *shell, char *str)
{
	char	*find;
	char	**ret;
	char	*tmp;

	tmp = NULL;
	find = ft_strdup(str);
	if (glob_check(str) == 1)
		tmp = glob_replace(shell, str);
	else if (glob_check(str) == 1 && !tmp)
	{
		glob_nomatch(find);
		tmp = ft_strdup(str);
	}
	ret = ft_strsplit(tmp, ' ');
	ft_putendl(ret[0]);
	ft_strdel(&tmp);
	ft_strdel(&find);
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
