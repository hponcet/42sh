/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 17:05:24 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 17:06:30 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_key_ctrl_d(void)
{
	if (g_curs.hd)
	{
		ft_putendl("");
		ft_heredoc_exec(g_curs.hd->trigger);
		ft_heredoc_del();
		ft_put_name();
		ft_init();
	}
	else if (g_curs.qt == 1)
		;
	else if (!g_curs.retval)
		ms_search_exit();
}
