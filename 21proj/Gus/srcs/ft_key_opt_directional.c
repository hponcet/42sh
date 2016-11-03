/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_opt_directional.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:28:50 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/25 17:58:47 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void		ft_key_opt_directional_up(void)
{
	t_chain		*tmp;

	tmp = g_curs.prev;
	if (g_curs.curs_pos[1] == g_curs.initpos[1] || !g_curs.next)
		return ;
	if (g_curs.curs_pos[0] <= g_curs.initpos[0] && g_curs.curs_pos[1] ==
			g_curs.initpos[1] + 1)
	{
		g_curs.prev = g_curs.chain;
		g_curs.next = g_curs.chain->next;
		g_curs.id = 1;
		tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1,
					g_curs.initpos[1] - 1), 1, ft_char);
	}
	else
	{
		while (tmp && tmp->prev->cp[0] >= 0 && tmp->cp[0] != g_curs.next->cp[0])
			tmp = tmp->prev;
		g_curs.prev = tmp->prev;
		g_curs.next = tmp;
		g_curs.id = tmp->id;
		tputs(tgoto(tgetstr("cm", 0), tmp->cp[0] - 1,
					tmp->cp[1] - 1), 1, ft_char);
	}
}

static void		ft_key_opt_directional_down(void)
{
	t_chain		*tmp;

	if (g_curs.curs_pos[1] == g_curs.ls->cp[1] || !g_curs.next)
		return ;
	tmp = g_curs.next->next;
	if (g_curs.curs_pos[0] >= g_curs.ls->cp[0] &&
			g_curs.curs_pos[1] == g_curs.ls->cp[1] - 1)
	{
		g_curs.prev = g_curs.ls->prev;
		g_curs.next = g_curs.ls;
		g_curs.id = g_curs.ls->id;
		tputs(tgoto(tgetstr("cm", 0), g_curs.ls->cp[0] - 1,
					g_curs.ls->cp[1] - 1), 1, ft_char);
	}
	else
	{
		while (tmp && tmp->cp[0] != g_curs.next->cp[0])
			tmp = tmp->next;
		g_curs.prev = tmp->prev;
		g_curs.next = tmp;
		g_curs.id = tmp->id;
		tputs(tgoto(tgetstr("cm", 0),
					tmp->cp[0] - 1, tmp->cp[1] - 1), 1, ft_char);
	}
}

static void		ft_key_opt_directional_left(void)
{
	t_chain		*tmp;

	if (!g_curs.chain)
		return ;
	if (!g_curs.next)
		tmp = g_curs.prev;
	else
		tmp = g_curs.next;
	if (g_curs.id == 1)
		return ;
	tmp = tmp->prev;
	while (tmp->word != 1)
		tmp = tmp->prev;
	g_curs.prev = tmp->prev;
	g_curs.next = g_curs.prev->next;
	if (tmp->id == 1)
		g_curs.id = 1;
	else
		g_curs.id = g_curs.next->id;
	tputs(tgoto(tgetstr("cm", 0), tmp->cp[0] - 1, tmp->cp[1] - 1), 1, ft_char);
}

static void		ft_key_opt_directional_right(void)
{
	t_chain		*tmp;

	if (!g_curs.chain)
		return ;
	if (g_curs.next)
		tmp = g_curs.next;
	else
		tmp = g_curs.prev;
	tmp = tmp->next;
	while (tmp && tmp->word != 1)
		tmp = tmp->next;
	if (!tmp)
		return ;
	g_curs.prev = tmp->prev;
	g_curs.next = g_curs.prev->next;
	g_curs.id = g_curs.next->id;
	tputs(tgoto(tgetstr("cm", 0), tmp->cp[0] - 1, tmp->cp[1] - 1), 1, ft_char);
}

void			ft_key_opt_directional(char *buf)
{
	if (buf[3] == 65)
		ft_key_opt_directional_up();
	if (buf[3] == 66)
		ft_key_opt_directional_down();
	if (buf[3] == 67)
		ft_key_opt_directional_right();
	if (buf[3] == 68)
		ft_key_opt_directional_left();
}
