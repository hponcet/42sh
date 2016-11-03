/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 18:18:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 17:29:42 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_char(int i)
{
	return (write(g_curs.fd, &i, 1));
}

int			ft_char_tc(t_chain *chr)
{
	int			v;

	write(g_curs.fd, &(chr->c), 1);
	v = g_curs.curs_pos[1];
	if (g_curs.prev->cp[0] == g_curs.ws[0])
	{
		tputs(tgetstr("do", 0), 1, ft_char);
		if (g_curs.curs_pos[0] == g_curs.ws[0] &&
				g_curs.curs_pos[1] == g_curs.ws[1])
		{
			g_curs.initpos[1] -= 1;
			g_curs.curs_pos[1] -= 1;
		}
	}
	ft_init_pos();
	ft_count_chain();
	return (1);
}

static void	ft_cursor_replace(void)
{
	int			h;
	int			v;

	h = g_curs.curs_pos[0];
	v = g_curs.curs_pos[1];
	if (g_curs.ls->cp[1] > g_curs.ws[1])
	{
		tputs(tgoto(tgetstr("cm", 0), h, v - 2), 1, ft_char);
		g_curs.initpos[1] -= 1;
		g_curs.curs_pos[1] -= 1;
	}
	else if (g_curs.curs_pos[0] == g_curs.ws[0])
		tputs(tgoto(tgetstr("cm", 0), 0, v), 1, ft_char);
	else
		tputs(tgoto(tgetstr("cm", 0), h, v - 1), 1, ft_char);
}

int			ft_str_tc(t_chain *chr)
{
	t_chain		*tmp;

	tmp = chr;
	tputs(tgoto(tgetstr("vi", 0), 1, 0), 1, ft_char);
	while (tmp)
	{
		if (tmp->sel == 1)
			tputs(tgetstr("mr", 0), 1, ft_char);
		else if (tmp->sel == 0)
			tputs(tgetstr("me", 0), 1, ft_char);
		tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
		ft_char(tmp->c);
		tmp = tmp->next;
	}
	tputs(tgetstr("me", 0), 1, ft_char);
	ft_cursor_replace();
	ft_init_pos();
	ft_count_chain();
	tputs(tgoto(tgetstr("ve", 0), 1, 0), 1, ft_char);
	return (1);
}

int			ft_char_count_sf(int len)
{
	int		i;
	int		line_asked;
	int		line_dispo;

	line_asked = len / g_curs.ws[0] + 1;
	line_dispo = g_curs.ws[1] - g_curs.initpos[1];
	i = line_asked - line_dispo;
	if (i > 0)
		return (i);
	else
		return (0);
}
