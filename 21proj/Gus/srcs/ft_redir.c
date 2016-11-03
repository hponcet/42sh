/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 14:25:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/25 18:36:15 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			ft_redir_exec(char *cmd)
{
	while (ft_cindex_noquote(cmd, '<') >= 0 || ft_cindex_noquote(cmd, '>')
			>= 0)
		ft_redir(&cmd);
	g_cmd = ms_parse_cmd(cmd);
}

void			ft_redir(char **cmd)
{
	int		i;

	if ((i = ft_cindex_noquote_rev(cmd[0], '>')) > 0)
	{
		if (cmd[0][i + 1] == '&')
			ft_redir_fd(cmd);
		else if (cmd[0][i - 1] == '>')
			ft_redir_double_right(cmd);
		else
			ft_redir_right(cmd);
	}
	else if ((i = ft_cindex_noquote_rev(cmd[0], '<') > 0) &&
			cmd[0][i + 1] != '<')
		ft_redir_left(cmd);
}

void			ft_redir_left(char **cmd)
{
	int		i;
	int		fd;
	char	*filename;

	filename = ft_redir_getfilename(cmd[0], '<');
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_putendl("21sh: Bad file name or can't access.");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	i = ft_cindex_noquote_rev(cmd[0], '<');
	ft_strdel(&filename);
	filename = ft_strdup(cmd[0]);
	free(cmd[0]);
	cmd[0] = ft_strsub(filename, 0, i);
	ft_strdel(&filename);
}
