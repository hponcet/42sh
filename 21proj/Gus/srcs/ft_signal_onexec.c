/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_onexec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 15:23:00 by hponcet           #+#    #+#             */
/*   Updated: 2016/09/16 15:39:49 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_signal_exit(void)
{
	signal(SIGINT, SIG_DFL);
	ft_putendl("");
}

static void	ft_catch_signal_onexec(int signo)
{
	if (signo == SIGINT)
		ft_signal_exit();
}

void		ft_signal_onexec(void)
{
	signal(SIGINT, ft_catch_signal_onexec);
}
