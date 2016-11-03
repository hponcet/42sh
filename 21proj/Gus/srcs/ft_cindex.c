/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cindex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:56:49 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 18:56:28 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

int		ft_cindex_count_quote(char *s, int i, char c)
{
	int		j;

	j = 1;
	i++;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

int		ft_cindex_count_quote_rev(char *s, int i, char c)
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

int		ft_cindex_noquote(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'' || str[i] == 96)
			i += ft_cindex_count_quote(str, i, str[i]);
		i++;
	}
	if (str[i] != c)
		return (-1);
	return (i);
}

int		ft_cindexfrom_noquote_rev(char *str, int index, char c)
{
	int		len;

	if (!str)
		return (-1);
	len = index;
	while (len > -1 && str[len] != c)
	{
		if (str[len] == '\"' || str[len] == '\'' || str[len] == 96)
			len -= ft_cindex_count_quote_rev(str, len, str[len]);
		len--;
	}
	return (len);
}

int		ft_cindex_noquote_rev(char *str, char c)
{
	int		len;

	if (!str)
		return (-1);
	len = ft_strlen(str) - 1;
	while (len > -1 && str[len] != c)
	{
		if (str[len] == '\"' || str[len] == '\'' || str[len] == 96)
			len -= ft_cindex_count_quote_rev(str, len, str[len]);
		len--;
	}
	return (len);
}
