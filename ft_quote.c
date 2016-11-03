/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 18:45:33 by MrRobot           #+#    #+#             */
/*   Updated: 2016/09/12 16:23:43 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_remove_quote_str(char *str)
{
	char	*result;
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((result = ft_treat_dollars(str, 0)) == NULL)
		result = ft_strnew((ft_strlen(str)));
	else
		return (result);
	while (str[i] != 0)
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '`')
		{
			c = str[i++];
			while (str[i] != c)
				result[j++] = str[i++];
			i++;
		}
		else
			result[j++] = str[i++];
	}
	return (result);
}

char		**ft_remove_quote_tab(char **tab)
{
	char	**cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = ft_tabnew(ft_tablen(tab));
	while (tab[i] != NULL)
	{
		cmd[j] = ft_remove_quote_str(tab[i]);
		i++;
		j++;
	}
	return (cmd);
}

void		ft_jump_quote(char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	while (str[*i] != c)
		(*i)++;
}
