/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 12:20:26 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/02 16:06:58 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_window_size(void)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	g_curs.ws[0] = win.ws_col;
	g_curs.ws[1] = win.ws_row;
}

static void	ft_init_window_find(size_t id)
{
	ft_str_tc(g_curs.chain);
	g_curs.initpos[1] = 1;
	g_curs.next = NULL;
	g_curs.prev = g_curs.ls;
	g_curs.id = g_curs.ls->id + 1;
	while (g_curs.id != id)
	{
		g_curs.id = g_curs.prev->id;
		g_curs.prev = g_curs.prev->prev;
	}
	g_curs.next = g_curs.prev->next;
}

void		ft_init_window(void)
{
	size_t		id;

	tputs(tgetstr("vi", 0), 0, ft_char);
	id = g_curs.id;
	ft_window_size();
	tputs(tgoto(tgetstr("cl", 0), 1, 0), 1, ft_char);
	ft_put_name();
	if (g_curs.chain)
		ft_init_window_find(id);
	ft_count_chain();
	ft_cursor_pos();
	ft_init_pos();
	if (!g_curs.chain)
		tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1,
					0), 1, ft_char);
	else if (id == 1)
		tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1,
					g_curs.initpos[1] - 1), 1, ft_char);
	else
		tputs(tgoto(tgetstr("cm", 0), g_curs.prev->cp[0],
					g_curs.prev->cp[1] - 1), 1, ft_char);
	tputs(tgetstr("ve", 0), 0, ft_char);
	ft_count_chain();
	ft_cursor_pos();
	ft_init_pos();
}
