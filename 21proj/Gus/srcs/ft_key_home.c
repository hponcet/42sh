/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 00:50:02 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 13:19:56 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_home(char *buf)
{
	if (!g_curs.chain)
		return ;
	if (buf[2] == 70)
	{
		g_curs.next = NULL;
		g_curs.prev = g_curs.ls;
		g_curs.id = g_curs.ls->id + 1;
		tputs(tgoto(tgetstr("cm", 0), g_curs.ls->cp[0],
					g_curs.ls->cp[1] - 1), 1, ft_char);
	}
	if (buf[2] == 72)
	{
		g_curs.next = g_curs.chain->next;
		g_curs.prev = g_curs.chain;
		g_curs.id = 1;
		tputs(tgoto(tgetstr("cm", 0), g_curs.chain->cp[0] - 1,
					g_curs.chain->cp[1] - 1), 1, ft_char);
	}
}
