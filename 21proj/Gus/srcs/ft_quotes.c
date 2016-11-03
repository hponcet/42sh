/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:05:16 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 12:40:33 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int				*ft_quote_initteub(void)
{
	int			*teub;

	teub = (int*)malloc(sizeof(int) * 5);
	teub[0] = 0;
	teub[1] = 0;
	teub[2] = 0;
	teub[3] = 0;
	teub[4] = 0;
	return (teub);
}

/*
** tq[0] : '
** tq[1] : "
** tq[2] : `
** tq[3] : {}
** tq[4] : ()
*/

static int		*ft_quote_find(char *retval)
{
	int			*tq;
	int			i;

	tq = ft_quote_initteub();
	i = -1;
	while (retval[++i])
	{
		if (retval[i] == 39 && tq[1] == 0 && tq[2] == 0)
			tq[0] = (tq[0] == 0) ? 1 : 0;
		if (retval[i] == 34 && tq[0] == 0 && tq[2] == 0)
			tq[1] = (tq[1] == 0) ? 1 : 0;
		if (retval[i] == 96)
			tq[2] = (tq[2] == 0) ? 1 : 0;
		if (retval[i] == '{' && tq[2] == 0 && tq[1] == 0 && tq[0] == 0)
			tq[3]++;
		if (retval[i] == '}' && tq[2] == 0 && tq[1] == 0 && tq[0] == 0)
			tq[3]--;
		if (retval[i] == '(' && tq[2] == 0 && tq[1] == 0 && tq[0] == 0)
			tq[4]++;
		if (retval[i] == ')' && tq[2] == 0 && tq[1] == 0 && tq[0] == 0)
			tq[4]--;
		if (retval[i] == 92)
			i++;
	}
	return (tq);
}

static int		ft_quote_prompt(int *tab_quote)
{
	if (tab_quote[0] > 0 || tab_quote[1] > 0 || tab_quote[2] > 0 ||
			tab_quote[3] > 0 || tab_quote[4] > 0)
	{
		if (tab_quote[0] > 0)
			ft_putstr_fd("quote ", g_curs.fd);
		if (tab_quote[1] > 0)
			ft_putstr_fd("dquote ", g_curs.fd);
		if (tab_quote[2] > 0)
			ft_putstr_fd("bquote ", g_curs.fd);
		if (tab_quote[3] > 0)
			ft_putstr_fd("cursh ", g_curs.fd);
		if (tab_quote[4] > 0)
			ft_putstr_fd("subsh ", g_curs.fd);
		ft_putstr_fd("> ", g_curs.fd);
		return (1);
	}
	return (0);
}

int				ft_quote(void)
{
	int		*tab_quote;
	char	*ret;

	ret = NULL;
	if (g_curs.tmpchain)
	{
		ret = (!g_curs.retval) ? ft_joinf("%s\n", g_curs.tmpchain)
		: ft_joinf("%s\n%s", g_curs.tmpchain, g_curs.retval);
		ft_strdel(&g_curs.tmpchain);
	}
	else
		ret = ft_strdup(g_curs.retval);
	tab_quote = ft_quote_find(ret);
	if (ft_quote_prompt(tab_quote) > 0)
	{
		g_curs.tmpchain = ret;
		free(tab_quote);
		return (1);
	}
	ft_strdel(&g_curs.retval);
	g_curs.retval = ft_strdup(ret);
	g_curs.qt = 0;
	ft_strdel(&ret);
	free(tab_quote);
	return (0);
}
