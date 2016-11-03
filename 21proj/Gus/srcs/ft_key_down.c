/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 08:52:16 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 13:35:23 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_down(void)
{
	if (!g_curs.history || g_curs.hist == 0)
		return ;
	tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1,
				g_curs.initpos[1] - 1), 1, ft_char);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
	if (g_curs.hist == 1 && !g_curs.history->next)
	{
		g_curs.hist = 0;
		if (g_curs.chain)
		{
			ft_str_tc(g_curs.chain);
			ft_count_chain();
			ft_init_pos();
			tputs(tgoto(tgetstr("cm", 0), g_curs.ls->cp[0], g_curs.ls->
						cp[1] - 1), 1, ft_char);
		}
		return ;
	}
	if (g_curs.history->next)
	{
		g_curs.history = g_curs.history->next;
		ft_putstr_fd(g_curs.history->cmd, g_curs.fd);
	}
}
