/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chain_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 17:56:12 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/02 16:07:41 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_chain_addstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_chain_addchar(str[i]);
		i++;
	}
}

void		ft_chain_addchar(int c)
{
	int		i;

	i = -1;
	if (g_curs.initpos[1] == 1 && g_curs.ls->cp[1] == g_curs.ws[1]
			&& g_curs.ls->cp[0] == g_curs.ws[0] - 1)
		return ;
	if (!g_curs.chain)
	{
		g_curs.chain = ft_new_chr(c);
		g_curs.prev = g_curs.chain;
		g_curs.id = 2;
		g_curs.chain->word = 1;
		ft_char_tc(g_curs.chain);
		return ;
	}
	if (!g_curs.next && g_curs.id != 1)
		ft_chain_lastchar(c);
	else if (g_curs.next && g_curs.id != 1)
		ft_chain_midchar(c);
	else if (g_curs.id == 1)
		ft_chain_firstchar(c);
	ft_count_chain();
}
