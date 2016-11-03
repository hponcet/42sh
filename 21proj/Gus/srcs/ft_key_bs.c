/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_bs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 01:25:28 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 02:33:12 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void		ft_key_bs_midline(void)
{
	g_curs.prev->prev->next = g_curs.next;
	g_curs.next->prev = g_curs.prev->prev;
	g_curs.prev = g_curs.prev->prev;
}

static void		ft_key_bs_firstchar(void)
{
	if (g_curs.chain->next)
	{
		g_curs.chain = g_curs.chain->next;
		g_curs.next->prev = g_curs.next;
		g_curs.next = g_curs.chain->next;
		if (g_curs.chain->c != ' ')
			g_curs.chain->word = 1;
	}
	else
	{
		g_curs.chain = NULL;
		g_curs.next = NULL;
	}
	g_curs.prev = g_curs.chain;
}

static void		ft_key_bs_lastchar(void)
{
	g_curs.prev->prev->next = NULL;
	g_curs.prev = g_curs.prev->prev;
}

static void		ft_key_bs_cursmove(void)
{
	if (g_curs.curs_pos[0] == 1)
	{
		tputs(tgoto(tgetstr("cm", 0), g_curs.ws[0],
					g_curs.curs_pos[1] - 2), 1, ft_char);
		tputs(tgoto(tgetstr("dc", 0), 1, 0), 1, ft_char);
		if (g_curs.next)
			ft_str_tc(g_curs.next);
		tputs(tgoto(tgetstr("cm", 0), g_curs.ws[0],
					g_curs.curs_pos[1] - 2), 1, ft_char);
	}
	else
	{
		tputs(tgoto(tgetstr("le", 0), 0, 0), 1, ft_char);
		tputs(tgoto(tgetstr("sc", 0), 0, 0), 1, ft_char);
		tputs(tgoto(tgetstr("dc", 0), 1, 0), 1, ft_char);
		ft_init_pos();
		if (g_curs.next && g_curs.id != 2)
			ft_str_tc(g_curs.next);
		else if (g_curs.id == 2 && g_curs.chain)
			ft_str_tc(g_curs.prev);
		if (!g_curs.next)
			tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
		tputs(tgoto(tgetstr("rc", 0), 0, 0), 1, ft_char);
	}
}

void			ft_key_bs(void)
{
	t_chain		*tmp;

	tmp = g_curs.prev;
	if (g_curs.next && g_curs.id > 2)
		ft_key_bs_midline();
	else if (g_curs.id == 2)
	{
		tmp = g_curs.chain;
		ft_key_bs_firstchar();
	}
	else if (g_curs.id != 1)
		ft_key_bs_lastchar();
	else if (g_curs.id == 1)
		return ;
	ft_count_chain();
	ft_init_pos();
	ft_key_bs_cursmove();
	g_curs.id -= 1;
	free(tmp->cp);
	tmp->next = NULL;
	tmp->prev = NULL;
	if (!g_curs.chain && g_curs.retval)
		ft_strdel(&g_curs.retval);
	free(tmp);
}
