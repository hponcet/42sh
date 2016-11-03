/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 20:16:42 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/18 01:29:36 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_term_init(void)
{
	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		ft_putendl_fd("Env required for TERM variable", g_curs.fd);
		exit(EXIT_FAILURE);
	}
	if (tcgetattr(0, &(g_curs.term.init)) == -1)
		exit(EXIT_FAILURE);
	if (tcgetattr(0, &(g_curs.term.mod)) == -1)
		exit(EXIT_FAILURE);
	if (tcgetattr(0, &(g_curs.term.curs_pos)) == -1)
		return (-1);
	g_curs.term.mod.c_lflag &= ~(ICANON | ECHO);
	g_curs.term.curs_pos.c_lflag &= ~(ICANON | ECHO | CREAD);
	g_curs.term.mod.c_cc[VMIN] = 1;
	g_curs.term.mod.c_cc[VTIME] = 0;
	if (tcsetattr(3, TCSANOW, &(g_curs.term.mod)) == -1)
		return (-1);
	return (0);
}

int		ft_term_reset(void)
{
	if (tcsetattr(3, TCSANOW, &(g_curs.term.mod)) == -1)
		return (-1);
	return (0);
}
