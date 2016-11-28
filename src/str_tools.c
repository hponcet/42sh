/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 16:42:14 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/25 16:28:25 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*strsub_env_var(char *s, int start)
{
	int		i;
	char	*ret;

	i = start;
	if (s[i + 1] && !ft_isspace(s[i + 1]) && s[i + 1] != '$')
	{
		i++;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
		ret = ft_strsub(s, (start + 1), (i - start - 1));
		return (ret);
	}
	return (NULL);
}

char	*str_replace_var(char *s, int start, int quote)
{
	size_t	len;
	char	*tmp;
	char	*ret;

	if (quote == 1)
		return (s);
	ret = s;
	if ((tmp = strsub_env_var(s, start)))
	{
		len = ft_strlen(tmp);
		if ((tmp = env_var_to_value(tmp)))
		{
			ret = ft_replace_str(s, start, (len + 1), tmp);
			free(tmp);
			free(s);
		}
		else
			free(tmp);
	}
	return (ret);
}

int		strrchr_outside_quotes(char *s, char to_find)
{
	int		i;
	char	c;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (ft_isquote(s[i]) && (c = s[i--]))
		{
			while (i >= 0 && s[i] != c)
				i--;
		}
		else if (s[i] == to_find && !is_chr_escaped(s, i))
			return (i);
		if (i >= 0)
			i--;
	}
	return (-1);
}

int		is_str_quoted(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (s[0] == '\'' && s[len - 1] == '\'')
		return (1);
	else if (s[0] == '"' && s[len - 1] == '"')
		return (2);
	else if (s[0] == '`' && s[len - 1] == '`')
		return (3);
	return (0);
}

char	*strdup_remove_quotes(char *s)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(s);
	tmp = ft_strsub(s, 1, len - 2);
	free(s);
	s = tmp;
	return (s);
}
