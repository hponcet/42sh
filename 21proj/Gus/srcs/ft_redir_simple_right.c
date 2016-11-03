/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_simple_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 17:56:46 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/25 18:31:58 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

static int	ft_redir_fdout(char *cmd)
{
	int		i;
	int		j;
	int		ret;
	char	*fdout;

	j = 0;
	i = ft_cindex_noquote_rev(cmd, '>');
	if (i >= 1 && ft_isdigit(cmd[i - 1]) == 0)
		return (STDOUT_FILENO);
	while (i >= 1 && cmd[i - 1] >= 48 && cmd[i - 1] <= 57)
	{
		i--;
		j++;
	}
	fdout = ft_strsub(cmd, i, j);
	ret = ft_atoi(fdout);
	ft_strdel(&fdout);
	return (ret);
}

void		ft_redir_right(char **cmd)
{
	int		fd;
	int		fdout;
	char	*filename;
	int		i;

	fdout = ft_redir_fdout(cmd[0]);
	i = ft_cindex_noquote_rev(cmd[0], '>') - 1;
	filename = ft_redir_getfilename(cmd[0], '>');
	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (ft_putendl("21sh: File creation has fails."));
	dup2(fd, fdout);
	i = ft_cindex_noquote_rev(cmd[0], '>') - 1;
	while (ft_isdigit(cmd[0][i]) == 1)
		i--;
	ft_strdel(&filename);
	filename = ft_strdup(cmd[0]);
	free(cmd[0]);
	cmd[0] = ft_strsub(filename, 0, i);
	ft_strdel(&filename);
}
