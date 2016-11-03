/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 11:20:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/26 14:42:15 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_compl_countfile(t_compl *print)
{
	t_compl	*tmp;
	int		count;

	count = 0;
	tmp = print;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void		ft_compl_display(t_compl *print, char *find)
{
	char	*buf;
	t_compl	*tmp;
	int		pos[2];

	pos[0] = g_curs.curs_pos[0];
	pos[1] = g_curs.curs_pos[1];
	tmp = print;
	tputs(tgoto(tgetstr("cm", 0), pos[0] - 1, pos[1] - 1), 1, ft_char);
	ft_putstr(print->name + ft_strlen(find));
	tputs(tgetstr("ce", 0), 1, ft_char);
	buf = ft_strnew(4);
	while (42)
	{
		if (g_curs.sig && ft_init())
			break ;
		if (ft_compl_key(buf, &tmp, find, pos) == 1)
			break ;
		ft_bzero(buf, 4);
		read(g_curs.fd, buf, 4);
		if ((buf[0] == 27 || buf[0] == 4) && buf[1] == 0 && ft_init_pn(buf[0]))
			break ;
	}
	g_curs.sig = 0;
	ft_compl_delchain(print);
	ft_strdel(&buf);
}
