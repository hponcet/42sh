/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 10:02:34 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 11:56:50 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_nchar		*ft_new_list_nchar(void)
{
	t_nchar		*list;

	list = (t_nchar*)malloc(sizeof(t_nchar));
	if (!list)
		return (NULL);
	list->last = g_lastindex;
	list->len = ft_strlen(g_bufret);
	list->next = NULL;
	g_lastindex = list->len;
	return (list);
}

void		ft_putstr_nchar(char const *s)
{
	t_nchar		*tmp;
	int			lastlen;

	lastlen = 0;
	tmp = g_addrncharlst;
	while (tmp)
	{
		write(1, s + tmp->last, tmp->len - tmp->last);
		ft_putchar(0);
		lastlen = tmp->len;
		tmp = tmp->next;
	}
	if (lastlen < (int)ft_strlen(g_bufret))
		write(1, s + lastlen, ft_strlen(s) - lastlen);
}

void		ft_lst_addend_nchar(void)
{
	t_nchar		*tmp;
	t_nchar		*list;

	list = ft_new_list_nchar();
	tmp = g_addrncharlst;
	if (g_addrncharlst == NULL)
		g_addrncharlst = list;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = list;
	}
}
