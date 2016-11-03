/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 07:10:18 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 17:33:05 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_key_up(void)
{
	if (!g_curs.history)
		return ;
	if (g_curs.history->prev && g_curs.hist == 1)
		g_curs.history = g_curs.history->prev;
	else if (g_curs.hist == 0)
		g_curs.hist = 1;
	tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1, g_curs.initpos[1] - 1),
			1, ft_char);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
	ft_putstr_fd(g_curs.history->cmd, g_curs.fd);
	if ((int)ft_strlen(g_curs.history->cmd) + g_curs.initpos[0] >
			g_curs.ws[0] && g_curs.ws[1] == g_curs.initpos[1])
		g_curs.initpos[1] -= ((int)ft_strlen(g_curs.history->cmd)
				+ g_curs.initpos[0]) / g_curs.ws[0];
	if (g_curs.hist == 0)
	{
		g_curs.hist = 1;
		return ;
	}
}
