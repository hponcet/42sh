/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redi_fd_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 13:55:56 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/16 15:30:59 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int		ft_redir_fdout(char *cmd)
{
	int		i;
	int		j;
	char	*fdout;

	j = 0;
	i = ft_cindex(cmd, '<') + 1;
	if (cmd[i + 1] == '-')
		return (-1);
	if (cmd[i + 1] < 48 || cmd[i + 1] > 57)
	{
		ft_putendl("21sh: Parse error.");
		exit(0);
	}
	while (cmd[i + 1] >= 48 && cmd[i + 1] <= 57)
	{
		i++;
		j++;
	}
	fdout = ft_strsub(cmd, ft_cindex(cmd, '>') + 2, j);
	return (ft_atoi(fdout));
}

static void		ft_redir_exit(int fd)
{
	ft_printf("21sh: %d: Bad file descriptor.\n", fd);
	exit(0);
}

static int		ft_redir_fdin(char *cmd)
{
	int		i;
	int		j;
	char	*fdin;

	j = 0;
	i = ft_cindex(cmd, '<');
	if (cmd[i - 1] < 48 || cmd[i - 1] > 57)
		return (1);
	while (cmd[i - 1] >= 48 && cmd[i - 1] <= 57)
	{
		i--;
		j++;
	}
	fdin = ft_strsub(cmd, i, j);
	return (ft_atoi(fdin));
}

void			ft_redir_fd_left(char *cmd)
{
	int		fdin;
	int		fdout;
	char	*tmp;
	int		i;

	i = 0;
	fdin = ft_redir_fdin(cmd);
	if ((fdout = ft_redir_fdout(cmd)) == -1)
	{
		close(fdin);
		i = ft_cindex(cmd, '<') - 1;
		while (cmd[i] >= 48 && cmd[i] <= 57)
			i--;
		tmp = ft_strsub(cmd, 0, i);
		g_cmd = ms_get_cmd(tmp);
		return ;
	}
	if (dup2(fdout, fdin) == -1)
		ft_redir_exit(fdout);
	i = ft_cindex(cmd, '<') - 1;
	while (cmd[i] >= 48 && cmd[i] <= 57)
		i--;
	tmp = ft_strsub(cmd, 0, i);
	g_cmd = ms_get_cmd(tmp);
}
