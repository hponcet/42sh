/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursh_compose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:34:00 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/28 16:41:55 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_cursh_compose(char **str)
{
	char	**tmp;
	char	*dup;
	char	*last_str;
	char	*endline;
	int		i;

	i = ft_cindex_rev(str[0], '}');
	endline = ft_strsub(str[0], i + 1, ft_strlen(str[0]) - i);
	ft_printf("str : %s\n", str[0]);
	ft_cursh_replace(str);
	tmp = NULL;
	tmp = ft_strsplit(str[0], ' ');
	ft_printf("str_replaced: %s\n\n", str[0]);
	i = 0;
	while (tmp[i])
		i++;
	last_str = ft_strdup(tmp[i - 1]);
	if (i >= 1 && ft_cursh_check(tmp[i - 1]))
		ft_strdel(&tmp[i - 1]);
	else
	{
		free_tab(tmp);
		ft_strdel(&last_str);
		return ;
	}
	i = -1;
	while (tmp[++i])
	{
		dup = ft_joinf("%s%s", tmp[i], last_str);
		ft_cursh_compose(&dup);
		free(tmp[i]);
		tmp[i] = dup;
	}
	ft_strdel(&last_str);
	free(str[0]);
	str[0] = ft_strnew(0);
	i = -1;
	while (tmp[++i])
		tmp[i] = ft_joinf("%xs%s", tmp[i], endline);
	i = 0;
	while (tmp[i])
		str[0] = ft_joinf("%xs %xs", str[0], tmp[i++]);
	free(tmp);
}


