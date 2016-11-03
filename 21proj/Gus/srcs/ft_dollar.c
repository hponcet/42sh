/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:50:27 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/22 18:05:48 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char		*ft_get_env_value(char *cmd)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_curs.env && g_curs.env[i])
	{
		if (ft_strncmp(cmd, g_curs.env[i], ft_strlen(cmd)) == 0)
		{
			j = ft_cindex(g_curs.env[i], '=') + 1;
			value = ft_strsub(g_curs.env[i], j, ft_strlen(g_curs.env[i]));
			return (value);
		}
		i++;
	}
	value = ft_strnew(0);
	return (value);
}

char		*ft_get_var_value(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	k = -1;
	ret = NULL;
	if ((i = ft_cindex(str, '$')) >= 0)
	{
		if (ft_cindex(str, 39) >= 0 && ft_cindex(str, 39) !=
				ft_cindex_rev(str, 39) && i > ft_cindex(str, 39)
				&& i < ft_cindex_rev(str, 39))
			return (NULL);
		j = i + 1;
		while (str[j] != ' ' && str[j] != '	' && str[j] != '\0' &&
				str[j] != '$' && str[j] != '"' &&
				str[j] != '`' && str[j] != '(' && str[j] != '(' &&
				str[j] != '{' && str[j] != '}')
			j++;
		ret = ft_strnew(j - i);
		while (++i < j)
			ret[++k] = str[i];
		return (ret);
	}
	return (NULL);
}

char		*ft_replace_cmd_var(char *cmd, char *var, char *value)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = ft_cindex(cmd, '$');
	ft_strlen(cmd);
	ft_strlen(value);
	ret = ft_strnew(ft_strlen(cmd) + ft_strlen(value));
	while (j < i)
	{
		ret[j] = cmd[j];
		j++;
	}
	i = 0;
	while (value[i])
		ret[j++] = value[i++];
	i = ft_cindex(cmd, '$') + ft_strlen(var) + 1;
	while (cmd[i])
		ret[j++] = cmd[i++];
	return (ret);
}

char		*ft_dollar(char *str)
{
	char	*ret;
	char	*ret_value;
	char	*var;

	var = ft_get_var_value(str);
	if (!var)
		return (str);
	ret_value = ft_get_env_value(var);
	ret = ft_replace_cmd_var(str, var, ret_value);
	if (ft_cindex(ret, '$') >= 0)
		ret = ft_dollar(ret);
	free(var);
	free(ret_value);
	return (ret);
}
