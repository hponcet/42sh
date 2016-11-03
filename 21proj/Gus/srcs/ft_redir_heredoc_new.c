/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:31:34 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/24 20:37:40 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				ft_heredoc_endtrig(char *str)
{
	int		i;

	i = ft_heredoc_check();
	while (g_curs.retval[i] == ' ' || g_curs.retval[i] == '	' ||
			g_curs.retval[i] == '<')
		i++;
	if (g_curs.retval[i] == '\0')
	{
		ft_heredoc_err(1);
		return (0);
	}
	while (str[i] && str[i] != ' ' && str[i] != '	')
		i++;
	return (i);
}

char			*ft_heredoc_initcmd(char *str)
{
	int		i;
	char	*ret;

	i = ft_heredoc_endtrig(str) + 1;
	if (i - 1 == (int)ft_strlen(str))
		return (NULL);
	ret = ft_strsub(str, i, ft_strlen(str) - i);
	return (ret);
}

char			*ft_heredoc_cmd(char *str)
{
	int		i;
	char	*ret;

	i = ft_heredoc_check();
	while ((g_curs.retval[i] == ' ' || g_curs.retval[i] == '	'
				|| g_curs.retval[i] == '<')
			&& i >= 0)
		i--;
	if (i == 0)
	{
		ft_heredoc_err(0);
		return (0);
	}
	ret = ft_strsub(str, 0, i + 1);
	return (ret);
}

int				ft_heredoc_new(void)
{
	int		i;

	g_curs.hd = (t_hd*)malloc(sizeof(t_hd));
	g_curs.hd->init_cmd = ft_heredoc_initcmd(g_curs.retval);
	g_curs.hd->cmd = ft_heredoc_cmd(g_curs.retval);
	i = ft_heredoc_check();
	while (g_curs.retval[i] == ' ' || g_curs.retval[i] == '	'
			|| g_curs.retval[i] == '<')
		i++;
	if (g_curs.retval[i] == '\0')
	{
		ft_heredoc_err(1);
		return (0);
	}
	g_curs.hd->trigger = ft_strsub(g_curs.retval, i,
			ft_heredoc_endtrig(g_curs.retval) - i);
	i = open("/tmp/.__21sh_tmp_hd", O_TRUNC | O_RDWR);
	close(i);
	ft_hist_addtohist(g_curs.retval);
	ft_strdel(&g_curs.retval);
	return (1);
}
