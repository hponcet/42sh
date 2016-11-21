/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_convert_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 05:07:54 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/21 06:05:11 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		tab_len(char **t)
{
	int		i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

char	**tab_copy(char **t)
{
	char	**ret;
	int		i;

	if (!t)
		return (NULL);
	i = tab_len(t);
	ret = (char**)malloc(sizeof(char*) * (i + 1));
	ret[i] = NULL;
	i = 0;
	while (t[i])
	{
		ret[i] = ft_strdup(t[i]);
		i++;
	}
	return (ret);
}

char	**join_tab_to_tab(char **tab1, char **tab2)
{
	int		len1;
	int		len2;
	char	**ret;

	if (!tab1 && !tab2)
		return (NULL);
	if (!tab1)
		return (tab_copy(tab2));
	if (!tab2)
		return (tab_copy(tab1));
	len1 = tab_len(tab1);
	len2 = tab_len(tab2);
	ret = (char**)malloc(sizeof(char*) * (len1 + len2) + 1);
	ret[len1 + len2] = NULL;
	len1 = -1;
	while (tab1[++len1])
		ret[len1] = ft_strdup(tab1[len1]);
	len2 = 0;
	while (tab2[len2])
		ret[len1++] = ft_strdup(tab2[len2++]);
	return (ret);
}

char	**join_str_to_tab(char **t, char *str)
{
	int		tlen;
	int		i;
	char	**ret;

	if (!t && !str)
		return (NULL);
	if (!t)
	{
		ret = (char**)malloc(sizeof(char*) * 2);
		ret[0] = ft_strdup(str);
		ret[1] = NULL;
		return (ret);
	}
	if (!str)
		return (tab_copy(t));
	i = -1;
	tlen = tab_len(t);
	ret = (char**)malloc(sizeof(char*) * tlen + 2);
	ret[tlen + 1] = NULL;
	while (t[++i])
		ret[i] = ft_strdup(t[i]);
	ret[i] = ft_strdup(str);
	return (ret);
}
