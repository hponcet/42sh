/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 21:07:50 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/18 00:05:31 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static unsigned int	ft_count_word(char const *s, char c)
{
	size_t				i;
	unsigned int		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			if (s[i + 1] != c && s[i + 1])
				count++;
			i++;
		}
		while (s[i] != c && s[i])
		{
			if (count == 0)
				count++;
			i++;
		}
	}
	return (count);
}

char				**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**tab;
	size_t	start;

	start = 0;
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len = ft_count_word(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	tab[len] = NULL;
	while (s[i] && j < len)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		tab[j++] = ft_strsub(s, start, (i - start));
	}
	return (tab);
}
