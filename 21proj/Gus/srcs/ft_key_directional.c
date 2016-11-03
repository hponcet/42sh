/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_directional.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 17:12:16 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/23 16:25:42 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_directional(const char *buf)
{
	if (buf[2] == 65)
		ft_key_up();
	else if (buf[2] == 66)
		ft_key_down();
	else if (buf[2] == 67)
		ft_key_right();
	else if (buf[2] == 68)
		ft_key_left();
}

void	ft_key_left(void)
{
	if (!g_curs.chain)
		return ;
	if (g_curs.id > 1)
	{
		g_curs.prev = g_curs.prev->prev;
		g_curs.next = g_curs.prev->next;
		g_curs.id -= 1;
		if (g_curs.curs_pos[0] == 1)
			tputs(tgoto(tgetstr("cm", 0), g_curs.ws[0],
						g_curs.curs_pos[1] - 2), 1, ft_char);
		else
			tputs(tgoto(tgetstr("le", 0), 1, 0), 1, ft_char);
	}
	ft_cursor_pos();
}

void	ft_key_right(void)
{
	if (!g_curs.chain)
		return ;
	if (g_curs.id < g_curs.nb_chr + 1)
	{
		if (!g_curs.next && g_curs.id == 1)
			g_curs.next = NULL;
		else if (g_curs.id != 1)
		{
			g_curs.prev = g_curs.next;
			g_curs.next = g_curs.next->next;
		}
		g_curs.id += 1;
		if (g_curs.curs_pos[0] == g_curs.ws[0])
			tputs(tgoto(tgetstr("cm", 0), 0, g_curs.curs_pos[1]), 1, ft_char);
		else
			tputs(tgoto(tgetstr("nd", 0), 1, 0), 1, ft_char);
	}
	ft_cursor_pos();
}
