/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 13:14:36 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 13:44:34 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_debug_un(void)
{
	if (g_curs.chain)
	{
		ft_putstr_fd("last_char = ", g_curs.fd);
		ft_putchar_fd(g_curs.ls->c, g_curs.fd);
		ft_putstr_fd(" / cp :", g_curs.fd);
		ft_putnbr_fd(g_curs.ls->cp[0], g_curs.fd);
		ft_putstr_fd("/", g_curs.fd);
		ft_putnbr_fd(g_curs.ls->cp[1], g_curs.fd);
	}
	tputs(tgoto(tgetstr("do", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	ft_putstr_fd("g_curs.error = ", g_curs.fd);
	ft_putnbr_fd(g_curs.error, g_curs.fd);
}

void		ft_debug_head(void)
{
	int		i;

	i = 0;
	ft_cursor_pos();
	tputs(tgoto(tgetstr("sc", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ho", 0), 1, 0), 1, ft_char);
	tputs(tgoto(tgetstr("ce", 0), 1, 0), 1, ft_char);
	while (i < g_curs.ws[0])
	{
		if (i == ((g_curs.ws[0] / 2) - 3))
		{
			ft_putstr(" DEBUG ");
			i += 7;
		}
		ft_putchar('#');
		i++;
	}
	ft_debug_un();
}
