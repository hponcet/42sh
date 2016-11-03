/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 11:27:06 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/24 19:24:08 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_minishell.h"

int		ms_get_nbc(char *buf)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (buf[i])
	{
		while ((buf[i] == ' ' || buf[i] == '	') && buf[i])
		{
			if (buf[i + 1] && buf[i + 1] != ' ' && buf[i + 1] != '	')
				count++;
			i++;
		}
		while (buf[i] != ' ' && buf[i] != '	' && buf[i])
		{
			if (count == 0)
				count++;
			i++;
		}
	}
	return (count);
}

char	**ms_get_cmd(char *buf)
{
	char	**cmd;
	int		i;
	int		j;
	int		start;
	int		len;

	i = 0;
	j = 0;
	start = 0;
	len = ms_get_nbc(buf);
	if (!(cmd = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	cmd[len] = NULL;
	while (buf[i] && j < len)
	{
		while (buf[i] == ' ' || buf[i] == '	')
			i++;
		start = i;
		while (buf[i] != ' ' && buf[i] != '	' && buf[i] != '\0')
			i++;
		cmd[j] = ft_strsub(buf, start, (i - start));
		j++;
	}
	return (cmd);
}

char	**ms_free_tab(char **teub)
{
	int		i;

	i = 0;
	if (!teub)
		return (NULL);
	while (teub[i])
	{
		free(teub[i]);
		teub[i] = NULL;
		i++;
	}
	free(teub);
	return (NULL);
}

void	ms_del_cmd(int l)
{
	int		len;
	char	**ncmd;
	int		i;
	int		j;

	j = -1;
	i = -1;
	len = 0;
	if (!g_cmd)
		return ;
	while (g_cmd[len])
		len++;
	if (!(ncmd = (char**)malloc(sizeof(char*) * len)))
		return ;
	ncmd[len - 1] = NULL;
	while (++i < len - 1)
	{
		if (++j == l)
			j++;
		ncmd[i] = ft_strdup(g_cmd[j]);
	}
	ft_tabdel(g_cmd);
	g_cmd = NULL;
	ncmd[0] ? g_cmd = ncmd : ft_tabdel(ncmd);
}
