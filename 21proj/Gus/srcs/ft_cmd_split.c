/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 21:27:35 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/24 15:50:13 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static unsigned int	ft_count_word(char const *s)
{
	size_t				i;
	unsigned int		count;

	count = 0;
	i = 0;
	while (s[i] == ';' && s[i + 1] == ';' && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == 92)
			i++;
		if (s[i] == 39)
			while (s[i] && s[i] != 39)
				i++;
		if (s[i] == '"')
			while (s[i] && s[i] != '"')
				i++;
		if (s[i] == ';' && count++)
			while (s[i + 1] == ';')
				i++;
		i++;
	}
	if (s[i] != ';')
		count++;
	return (count);
}

int					ft_cmd_count_quote(char *s, int i, char c)
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

static char			**ft_cmd_parse(char **teub, char *s)
{
	int		i;
	int		j;
	size_t	start;

	j = 0;
	i = 0;
	while (s[i] && (s[i] == ';' || s[i] == ' ' || s[i] == '	'))
		i++;
	start = i;
	while (s[i])
	{
		if (s[i] && (s[i] == 39 || s[i] == '"' || s[i] == 92))
			i += ft_cmd_count_quote(s, i, s[i]);
		if (s[i] == ';')
		{
			teub[j] = ft_strsub(s, start, (i - start));
			j++;
			while (s[i + 1] == ';')
				i++;
			start = i + 1;
		}
		i++;
	}
	teub[j] = ((int)start != i) ? ft_strsub(s, start, (i - start)) : NULL;
	return (teub);
}

char				**ft_cmd_split(char *s)
{
	size_t	i;
	size_t	len;
	char	**teub;

	i = -1;
	if (!s)
		return (NULL);
	len = ft_count_word(s);
	teub = (char**)malloc(sizeof(char*) * (len + 1));
	while (++i <= len)
		teub[i] = NULL;
	teub = ft_cmd_parse(teub, s);
	return (teub);
}
