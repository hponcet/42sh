/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 17:38:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 17:00:11 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_redir_isgoodchar(char i)
{
	if ((i >= 33 && i <= 126) && i != '|' && i != '<' && i != '>' && i != '\0'
			&& i != '`' && i != ' ' && i != '	')
		return (1);
	else
		return (0);
}

char		*ft_redir_getfilename(char *cmd, char c)
{
	char	*filename;
	int		i;
	int		j;

	i = ft_cindex_noquote_rev(cmd, c) + 1;
	while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '	'))
		i++;
	j = i;
	while (ft_redir_isgoodchar(cmd[j]) == 1)
		j++;
	if (j - i + 1 < 1)
	{
		ft_putendl("21sh: Parse error.");
		exit(EXIT_FAILURE);
	}
	filename = ft_strnew(j - i);
	j = 0;
	while (cmd[i] && ft_redir_isgoodchar(cmd[i]) == 1)
	{
		filename[j] = cmd[i];
		j++;
		i++;
	}
	return (filename);
}
