/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_double_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:08:37 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 02:06:32 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		ft_redir_fdout(char *cmd)
{
	int		i;
	int		j;
	int		ret;
	char	*fdout;

	j = 0;
	i = ft_cindex_noquote_rev(cmd, '>') - 1;
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

void			ft_redir_double_right(char **cmd)
{
	int		t[4];
	char	*filename;

	t[1] = 0;
	t[0] = ft_cindex_noquote(cmd[0], '>');
	t[3] = ft_redir_fdout(cmd[0]);
	filename = ft_redir_getfilename(cmd[0], '>');
	if ((t[2] = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		return (ft_putendl("21sh: File creation has fails."));
	dup2(t[2], t[3]);
	t[0] = ft_cindex_noquote_rev(cmd[0], '>') - 2;
	while (cmd[0][t[0]] >= '0' && cmd[0][t[0]] >= '9')
		t[0]--;
	ft_strdel(&filename);
	filename = ft_strdup(cmd[0]);
	free(cmd[0]);
	cmd[0] = ft_strsub(filename, 0, t[0]);
	ft_strdel(&filename);
}
