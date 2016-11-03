/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 19:48:20 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 16:30:41 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_catch_signal(int signo)
{
	if (signo == SIGWINCH)
		ft_init_window();
	if (signo == SIGINT)
	{
		g_curs.sig = 1;
		ft_init_prompt();
	}
}

void		ft_signal(void)
{
	signal(SIGWINCH, ft_catch_signal);
	signal(SIGINT, ft_catch_signal);
}
