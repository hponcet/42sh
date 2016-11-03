/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 09:20:53 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 02:32:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_key_del_char(void)
{
	if (g_curs.next->next)
	{
		g_curs.next->next->prev = g_curs.prev;
		g_curs.prev->next = g_curs.next->next;
		g_curs.next = g_curs.prev->next;
	}
	else
	{
		g_curs.next = NULL;
		g_curs.prev->next = NULL;
	}
}

static void	ft_key_del_firstchar(void)
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

static void	ft_key_del_cursormove(void)
{
	if (g_curs.next && g_curs.id != 1)
	{
		tputs(tgoto(tgetstr("sc", 0), 1, 0), 1, ft_char);
		ft_str_tc(g_curs.next);
		tputs(tgoto(tgetstr("rc", 0), 1, 0), 1, ft_char);
	}
	else if (g_curs.id == 1 && g_curs.chain)
	{
		tputs(tgoto(tgetstr("sc", 0), 1, 0), 1, ft_char);
		ft_str_tc(g_curs.prev);
		tputs(tgoto(tgetstr("rc", 0), 1, 0), 1, ft_char);
	}
	else
	{
		tputs(tgoto(tgetstr("sc", 0), 1, 0), 1, ft_char);
		tputs(tgoto(tgetstr("dc", 0), 1, 0), 1, ft_char);
		tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
		tputs(tgoto(tgetstr("rc", 0), 1, 0), 1, ft_char);
	}
}

void		ft_key_del(void)
{
	t_chain		*tmp;

	if (!g_curs.next && g_curs.id != 1)
		return ;
	tmp = g_curs.next;
	if (g_curs.id == 1)
	{
		tmp = g_curs.prev;
		ft_key_del_firstchar();
	}
	else
		ft_key_del_char();
	ft_count_chain();
	ft_key_del_cursormove();
	free(tmp->cp);
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp);
}
