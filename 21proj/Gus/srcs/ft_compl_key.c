/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 20:20:22 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/25 16:51:02 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_compl_key_dir(char *buf, t_compl **print, char *find, int *pos)
{
	t_compl		*tmp;

	tmp = print[0];
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		tmp = tmp->prev;
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		tmp = tmp->next;
	else if (buf[0] == 27 && buf[1] == 0)
		return (ft_compl_retstr(*print, find, pos, 1));
	print[0] = tmp;
	return (0);
}

int			ft_compl_key(char *buf, t_compl **print, char *find, int *pos)
{
	t_compl		*tmp;

	tmp = print[0];
	if (tmp->next == tmp)
		return (ft_compl_retstr(tmp, find, pos, 1));
	if (buf[0] == 10)
		return (ft_compl_retstr(tmp, find, pos, 1));
	else if (buf[0] == 27 && ft_compl_key_dir(buf, &tmp, find, pos) == 1)
		return (1);
	else if (buf[0] == 9 && buf[1] == 0)
	{
		if (tmp == tmp->next)
			return (ft_compl_retstr(tmp, find, pos, 0));
		tmp = tmp->next;
	}
	else if (ft_isprint(buf[0]) == 1 && buf[1] == 0)
		return (ft_compl_retstrchar(tmp, find, pos, buf[0]));
	else if (buf[0] == 127 && buf[1] == 0)
		return (ft_compl_retstr(tmp, find, pos, 0));
	tputs(tgoto(tgetstr("cm", 0), pos[0] - 1, pos[1] - 1), 1, ft_char);
	ft_putstr(tmp->name + ft_strlen(find));
	tputs(tgetstr("ce", 0), 1, ft_char);
	*print = tmp;
	return (0);
}
