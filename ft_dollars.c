/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 15:00:52 by MrRobot           #+#    #+#             */
/*   Updated: 2016/09/06 12:27:18 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_treat_dollars(char *str, int j)
{
	int		i;
	char	*var;
	char	*val;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\'')
			j = (j == 0) ? 1 : 0;
		if (str[i] == '$' && j == 0)
		{
			if ((var = ft_set_var_dollars(str, i + 1)) == NULL)
				return (NULL);
			val = ft_return_path(var, g_shell.env);
			free(var);
			str = ft_strsub(str, 0, i);
			var = ft_str_add_str_index(str, val, ft_strlen(str));
			free(val);
			free(str);
			return (var);
		}
		i++;
	}
	return (NULL);
}

char	*ft_set_var_dollars(char *str, int i)
{
	char	*var;
	char	*tmp;
	int		save;

	save = i;
	while (str[i] != 0 && ft_isspace(str[i]) == 0 && str[i] != '"')
		i++;
	var = ft_strsub(str, save, i - save);
	if ((tmp = ft_return_path(var, g_shell.env)) == NULL)
	{
		free(var);
		return (NULL);
	}
	free(tmp);
	return (var);
}
