/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 18:17:43 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 01:37:11 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int		ft_redir_fdin(char *cmd)
{
	int		i;
	int		j;
	char	*fdin;
	int		ret;

	j = 0;
	i = ft_cindex_noquote_rev(cmd, '>') + 2;
	if (cmd[i] == '-')
		return (-1);
	if (ft_isdigit(cmd[i]) == 0)
	{
		ft_putendl("21sh: Parse error.");
		exit(0);
	}
	j = i;
	while (ft_isdigit(cmd[j]) == 1)
		j++;
	fdin = ft_strsub(cmd, i, j);
	ret = ft_atoi(fdin);
	ft_strdel(&fdin);
	return (ret);
}

static void		ft_redir_exit(int fd)
{
	fd = 1;
	ft_putendl("21sh: Bad file descriptor.");
	exit(0);
}

static int		ft_redir_fdout(char *cmd)
{
	int		i;
	int		j;
	int		ret;
	char	*fdout;

	j = 0;
	i = ft_cindex_noquote_rev(cmd, '>') - 1;
	if (ft_isdigit(cmd[i]) == 0)
		return (STDOUT_FILENO);
	while (i >= 1 && cmd[i] >= 48 && cmd[i] <= 57)
	{
		i--;
		j++;
	}
	fdout = ft_strsub(cmd, i + 1, j);
	ret = ft_atoi(fdout);
	ft_strdel(&fdout);
	return (ret);
}

void			ft_redir_fd(char **cmd)
{
	int		fdin;
	int		fdout;
	char	*tmp;
	int		i;

	i = 0;
	fdout = ft_redir_fdout(cmd[0]);
	fdin = ft_redir_fdin(cmd[0]);
	if (fdin == -1)
		close(fdout);
	else
	{
		if (dup2(fdin, fdout) == -1)
			ft_redir_exit(fdin);
	}
	i = ft_cindex_noquote_rev(cmd[0], '>') - 1;
	if (i > 0 && cmd[0][i] == '>')
		i--;
	while (ft_isdigit(cmd[0][i]) == 1)
		i--;
	tmp = ft_strdup(cmd[0]);
	free(cmd[0]);
	cmd[0] = ft_strsub(tmp, 0, i);
	ft_strdel(&tmp);
}
