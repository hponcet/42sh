/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_enter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 09:09:32 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 13:32:44 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_key_enter(void)
{
	tcsetattr(3, TCSANOW, &(g_curs.term.init));
	ft_putendl_fd("", g_curs.fd);
	if (!g_curs.retval && g_curs.qt == 0 && g_curs.hd == NULL)
		return (1);
	if (g_curs.hd == NULL && ft_quote() > 0)
	{
		g_curs.qt = 1;
		return (0);
	}
	if (ft_heredoc_check() > -1 || g_curs.hd)
	{
		ft_heredoc_proc();
		ft_init();
		if (g_curs.hd)
			return (0);
		else
			return (1);
	}
	if (!g_curs.retval)
		return (0);
	ft_signal_onexec();
	ft_cmd(g_curs.retval);
	ft_hist_addtohist(g_curs.retval);
	tcsetattr(3, TCSANOW, &(g_curs.term.mod));
	return (1);
}
