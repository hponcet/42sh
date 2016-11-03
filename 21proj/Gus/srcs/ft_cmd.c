/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:55:44 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/25 18:42:30 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void	ft_cmd_foot(char **tmp)
{
	g_moddedenv = 0;
	ft_strdel(tmp);
	if (g_cmd)
		ft_tabdel(g_cmd);
	g_cmd = NULL;
}

void	ft_cmd(char *enter)
{
	char	**cmd;
	char	*tmp;
	int		i;

	if (ft_cindex(enter, '$') >= 0)
		enter = ft_dollar(enter);
	cmd = ft_cmd_split(enter);
	i = 0;
	while (cmd[i])
	{
		if (ft_alias(cmd[i]) && ++i)
			continue ;
		if (!(tmp = ft_glob(cmd[i])) && ++i)
			continue ;
		g_cmd = ms_parse_cmd(tmp);
		ms_exec(tmp, g_curs.env);
		ft_cmd_foot(&tmp);
		i++;
	}
	ft_tabdel(cmd);
}
