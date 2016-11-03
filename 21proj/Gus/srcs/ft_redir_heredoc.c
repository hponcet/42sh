/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 22:44:14 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 01:43:08 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void			ft_heredoc_err(int i)
{
	if (i == 0)
		ft_putendl_fd("21sh: heredoc: Bad command.", g_curs.fd);
	if (i == 1)
		ft_putendl_fd("21sh: heredoc: Bad trigger.", g_curs.fd);
	if (i == 2)
	{
		ft_putendl_fd("21sh: heredoc: Can't acces to /tmp dir.", g_curs.fd);
		exit(0);
	}
	if (i == 3)
		ft_putendl_fd("21sh: heredoc: Can't access to /tmp dir.", g_curs.fd);
	ft_strdel(&(g_curs.hd->cmd));
	ft_strdel(&(g_curs.hd->init_cmd));
	free(g_curs.hd);
	g_curs.hd = NULL;
}

int				ft_heredoc_addcontent(char *str)
{
	int		fd;
	char	ret;

	ret = '\n';
	fd = -1;
	if (!str)
		str = ft_strdup("");
	if (access("/tmp/.__21sh_tmp_hd", W_OK) == 0)
	{
		fd = open("/tmp/.__21sh_tmp_hd", O_APPEND | O_RDWR);
		if (fd < 0)
			return (0);
		write(fd, str, ft_strlen(str));
		write(fd, &ret, 1);
		close(fd);
		return (1);
	}
	fd = open("/tmp/.__21sh_tmp_hd", O_CREAT | O_WRONLY);
	if (fd < 0)
		return (0);
	write(fd, str, ft_strlen(str));
	write(fd, &ret, 1);
	close(fd);
	return (1);
}

int				ft_heredoc_exec(char *str)
{
	char	*cmd;

	cmd = NULL;
	if (ft_strcmp(str, g_curs.hd->trigger) == 0)
	{
		if (g_curs.hd->init_cmd)
			cmd = ft_joinf("%s < /tmp/.__21sh_tmp_hd %s",
					g_curs.hd->cmd, g_curs.hd->init_cmd);
		else
			cmd = ft_joinf("%s < /tmp/.__21sh_tmp_hd", g_curs.hd->cmd);
		ft_cmd(cmd);
		ft_strdel(&cmd);
		return (1);
	}
	else
		return (0);
}

void			ft_heredoc_proc(void)
{
	if (!g_curs.hd && ft_heredoc_new() > 0)
	{
		ft_strdel(&g_curs.retval);
		ft_putstr_fd("heredoc> ", g_curs.fd);
		return ;
	}
	if (!g_curs.hd)
		return ;
	if ((g_curs.hd && !g_curs.retval) || ft_heredoc_exec(g_curs.retval) == 0)
	{
		if (ft_heredoc_addcontent(g_curs.retval) == 0)
			return ;
		ft_putstr_fd("heredoc> ", g_curs.fd);
		ft_strdel(&g_curs.retval);
		return ;
	}
	else
		ft_heredoc_del();
	ft_strdel(&g_curs.retval);
}
