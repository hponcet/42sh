/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 08:48:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 12:14:33 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_debug_deux(void)
{
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("Cursor : cur_pos = ", g_curs.fd);
	ft_putnbr_fd(g_curs.curs_pos[0], g_curs.fd);
	ft_putstr_fd("/", g_curs.fd);
	ft_putnbr_fd(g_curs.curs_pos[1], g_curs.fd);
	ft_putstr_fd(" P&Nchar = ", g_curs.fd);
	if (g_curs.prev)
		ft_putchar_fd(g_curs.prev->c, g_curs.fd);
	ft_putnbr_fd(g_curs.id, g_curs.fd);
	if (g_curs.next)
		ft_putchar_fd(g_curs.next->c, g_curs.fd);
	if (g_curs.prev)
	{
		ft_putstr_fd(" prev_pos = ", g_curs.fd);
		ft_putnbr_fd(g_curs.prev->cp[0], g_curs.fd);
		ft_putstr_fd("/", g_curs.fd);
		ft_putnbr_fd(g_curs.prev->cp[1], g_curs.fd);
	}
}

static void	ft_debug_trois(void)
{
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	if (g_curs.chain)
	{
		ft_putstr_fd("chain : c = ", g_curs.fd);
		ft_putchar_fd(g_curs.chain->c, g_curs.fd);
		ft_putstr_fd(" id = ", g_curs.fd);
		ft_putnbr_fd(g_curs.chain->id, g_curs.fd);
		ft_putstr_fd(" cp = ", g_curs.fd);
		ft_putnbr_fd(g_curs.chain->cp[0], g_curs.fd);
		ft_putstr_fd("/", g_curs.fd);
		ft_putnbr_fd(g_curs.chain->cp[1], g_curs.fd);
	}
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("Info : nb_chr = ", g_curs.fd);
	ft_putnbr_fd(g_curs.nb_chr, g_curs.fd);
	if (g_curs.chain)
	{
		if (g_curs.prev && g_curs.prev->word == 1)
			ft_putstr_fd(" |word|", g_curs.fd);
	}
}

static void	ft_debug_quatre(void)
{
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("Winsize = ", g_curs.fd);
	ft_putnbr_fd(g_curs.ws[0], g_curs.fd);
	ft_putstr_fd("/", g_curs.fd);
	ft_putnbr_fd(g_curs.ws[1], g_curs.fd);
	ft_putstr_fd(" initpos = ", g_curs.fd);
	ft_putnbr_fd(g_curs.initpos[0], g_curs.fd);
	ft_putstr_fd("/", g_curs.fd);
	ft_putnbr_fd(g_curs.initpos[1], g_curs.fd);
}

static void	ft_debug_cinq(void)
{
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("retval = ", g_curs.fd);
	ft_printf("%s", g_curs.retval);
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("copy = ", g_curs.fd);
	if (g_curs.history)
		ft_printf("%s", g_curs.copy);
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("moddedenv = ", g_curs.fd);
	ft_printf("%i", g_moddedenv);
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	if (g_curs.hd)
	{
		ft_putstr_fd("hd.trigger = ", g_curs.fd);
		ft_printf("%s / hd.cmd = %s|", g_curs.hd->trigger,
				g_curs.hd->cmd);
	}
}

void		ft_debug(void)
{
	int		i;

	i = 0;
	ft_debug_head();
	ft_debug_deux();
	ft_debug_trois();
	ft_debug_quatre();
	ft_debug_cinq();
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	while (i < g_curs.ws[0])
	{
		ft_putchar('#');
		i++;
	}
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("rc", 0), 1, 0), 1, ft_char);
}
