/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 06:13:38 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 17:57:23 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_chain			*ft_new_chr(int c)
{
	t_chain	*chr;

	if (!(chr = (t_chain*)malloc(sizeof(t_chain))))
		return (NULL);
	chr->c = c;
	chr->word = 0;
	chr->cp = (int*)malloc(sizeof(int) * 2);
	chr->cp[0] = g_curs.curs_pos[0];
	chr->cp[1] = g_curs.curs_pos[1];
	chr->sel = 0;
	chr->id = ++(g_curs.nb_chr);
	chr->prev = chr;
	chr->next = NULL;
	return (chr);
}

void			ft_chain_firstchar(int c)
{
	t_chain		*new;

	new = ft_new_chr(c);
	g_curs.prev->prev = new;
	new->next = g_curs.prev;
	g_curs.next = g_curs.prev;
	g_curs.prev = new;
	g_curs.chain = new;
	g_curs.id += 1;
	ft_count_chain();
	ft_char_tc(new);
	ft_str_tc(g_curs.next);
	ft_count_chain();
}

void			ft_chain_midchar(int c)
{
	t_chain		*new;

	new = ft_new_chr(c);
	g_curs.prev->next = new;
	new->prev = g_curs.prev;
	g_curs.next->prev = new;
	new->next = g_curs.next;
	g_curs.prev = new;
	g_curs.id += 1;
	ft_count_chain();
	ft_char_tc(new);
	ft_str_tc(new->next);
	ft_count_chain();
}

void			ft_chain_lastchar(int c)
{
	t_chain		*new;

	new = ft_new_chr(c);
	g_curs.prev->next = new;
	new->prev = g_curs.prev;
	g_curs.prev = new;
	g_curs.id = new->id + 1;
	ft_count_chain();
	ft_char_tc(new);
}
