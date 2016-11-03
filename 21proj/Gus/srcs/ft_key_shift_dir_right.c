/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_shift_dir_right.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 20:50:56 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 12:53:10 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_shift_dir_right_norm(void)
{
	if (g_curs.id == 1)
		tputs(tgoto(tgetstr("nd", 0), 1, 1), 1, ft_char);
	else
	{
		g_curs.prev = g_curs.prev->next;
		g_curs.next = g_curs.next->next;
	}
	g_curs.id += 1;
	g_curs.prev->sel = (g_curs.prev->sel == 0) ? 1 : 0;
	if (g_curs.select == NULL)
		g_curs.select = g_curs.prev;
}

void		ft_shift_dir_right(void)
{
	if (!g_curs.chain || !g_curs.next || g_curs.id > g_curs.nb_chr)
		return ;
	ft_init_pos();
	if (g_curs.id == 2)
	{
		g_curs.next->sel = (g_curs.next->sel == 0) ? 1 : 0;
		g_curs.prev = g_curs.prev->next;
		g_curs.id += 1;
		if (g_curs.select == NULL)
			g_curs.select = g_curs.prev;
	}
	else
		ft_shift_dir_right_norm();
	tputs(tgoto(tgetstr("cm", 0), g_curs.select->cp[0] - 1,
				g_curs.select->cp[1] - 1), 1, ft_char);
	ft_str_tc(g_curs.select);
	tputs(tgoto(tgetstr("cm", 0), g_curs.prev->cp[0] - 1,
				g_curs.prev->cp[1]) - 1, 1, ft_char);
	if (g_curs.id > g_curs.nb_chr)
		g_curs.next = NULL;
}

void		ft_reset_select(void)
{
	t_chain		*tmp;

	ft_init_pos();
	tmp = g_curs.chain;
	while (tmp)
	{
		if (tmp->sel == 1)
			tmp->sel = 0;
		tmp = tmp->next;
	}
	tputs(tgoto(tgetstr("cm", 0), g_curs.select->cp[0] - 1,
				g_curs.select->cp[1] - 1), 1, ft_char);
	ft_str_tc(g_curs.select);
	tputs(tgoto(tgetstr("le", 0), g_curs.select->cp[0] - 1,
				g_curs.select->cp[1] - 1), 1, ft_char);
	g_curs.select = NULL;
	ft_init_pos();
}
