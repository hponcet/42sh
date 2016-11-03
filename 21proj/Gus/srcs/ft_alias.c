/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 16:29:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/02 16:08:16 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_alias(char *str)
{
	char	**cmd;
	int		i;

	i = 0;
	if (!str)
		return (0);
	cmd = ms_parse_cmd(str);
	if (ft_strcmp(cmd[0], "alias") == 0 && cmd[1])
		i = ft_alias_new(cmd);
	else if (ft_strcmp(cmd[0], "unalias") == 0 && cmd[1])
		i = ft_alias_unalias(cmd[1]);
	else
		i = ft_alias_search(cmd);
	ft_tabdel(cmd);
	return (i);
}

int		ft_alias_unalias(char *cmd)
{
	int		index;
	t_hash	*tmp;
	t_hash	*prev;

	index = ft_hash(cmd, __HTBL_LEN__);
	tmp = g_curs.alias[index];
	prev = NULL;
	if (tmp)
	{
		while (tmp && ft_strcmp(tmp->name, cmd) != 0 && (prev = tmp))
			tmp = tmp->next;
		if (ft_strcmp(tmp->name, cmd) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				g_curs.alias[index] = tmp->next;
			ft_strdel(&tmp->name);
			ft_strdel(&tmp->value);
			free(tmp);
		}
	}
	ft_alias_htbltofile();
	ft_alias_gethtbl();
	return (1);
}

int		ft_alias_search(char **cmd)
{
	char	*ret;

	if ((ret = ft_hash_search(g_curs.alias, cmd[0], __HTBL_LEN__)))
	{
		ft_cmd(ret);
		if (g_cmd)
		{
			ft_tabdel(g_cmd);
			g_cmd = NULL;
		}
		ft_strdel(&ret);
		return (1);
	}
	return (0);
}

int		ft_alias_new(char **cmd)
{
	char	**unal;
	char	*tmp;
	int		i;

	i = ft_cindex(cmd[1], '=');
	unal = NULL;
	if (i >= 1 && cmd[1][i + 1] && (unal = ft_strsplit(cmd[1], '=')))
	{
		if ((tmp = ft_hash_search(g_curs.alias, unal[1], __HTBL_LEN__))
				|| ft_strcmp(unal[0], unal[1]) == 0)
		{
			ft_strdel(&tmp);
			ft_tabdel(unal);
			return (1);
		}
		ft_alias_unalias(unal[0]);
		ft_alias_htbladd(cmd[1]);
		ft_alias_htbltofile();
		ft_alias_gethtbl();
		ft_tabdel(unal);
		unal = NULL;
	}
	else
		ft_printf("alias: usage: alias [name[=\"value\"] ... ]\n");
	return (1);
}
