/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 05:58:21 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 17:13:36 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_reinit_hist(void)
{
	ft_histtochain();
	ft_init_pos();
	ft_count_chain();
	g_curs.hist = 0;
	g_curs.next = NULL;
	g_curs.prev = g_curs.ls;
}

static void	ft_enter(void)
{
	if (ft_key_enter() == 1)
		ft_put_name();
	ft_init();
}

void		ft_key_group_dir(char *buf)
{
	if (buf[1] == 91 && buf[2] == 51 && buf[3] == 126 &&
			buf[4] == 0 && g_curs.chain)
		ft_key_del();
	if (buf[1] == 91 && buf[2] >= 65 && buf[2] <= 68 && buf[3] == 0)
		ft_key_directional(buf);
	if (buf[1] == 27 && buf[2] == 91 && buf[3] >= 65 &&
			buf[3] <= 68 && g_curs.chain)
		ft_key_opt_directional(buf);
	if (buf[1] == 91 && (buf[2] == 70 || buf[2] == 72) && g_curs.chain)
		ft_key_home(buf);
}

void		ft_key_norm(void)
{
	if (g_curs.opt->dbg)
		ft_debug();
	if (!g_curs.chain)
		ft_strdel(&g_curs.retval);
	ft_cursor_pos();
	ft_count_chain();
	ft_init_pos();
}

void		ft_key(char *buf)
{
	if (g_curs.hist == 1 && (buf[0] != 27 || buf[1] != 91 ||
				(buf[2] != 65 && buf[2] != 66)))
		ft_reinit_hist();
	if (g_curs.select && (buf[0] != -30 && buf[0] != -61 && buf[3] != 59))
		ft_reset_select();
	if (buf[0] == 10)
		ft_enter();
	else if (buf[0] == 4 && buf[1] == 0)
		ft_key_ctrl_d();
	else if (buf[0] == 9 && buf[1] == 0 && !g_curs.next)
		ft_compl(g_curs.retval);
	else if (ft_isprint(buf[0]) == 1 && buf[1] == 0)
		ft_chain_addchar(buf[0]);
	else if (buf[0] == 127 && buf[1] == 0 && g_curs.chain)
		ft_key_bs();
	else if (buf[0] == 18 && buf[1] == 0 && !g_curs.chain)
		ft_hsearch();
	else if (buf[0] == 27)
		ft_key_group_dir(buf);
	else
		ft_cmd_v(buf);
	ft_key_norm();
}
