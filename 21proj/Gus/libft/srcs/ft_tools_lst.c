/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 00:57:46 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 22:07:50 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_lst_new(void)
{
	t_print		*list;

	list = (t_print*)malloc(sizeof(t_print));
	if (!list)
		return (NULL);
	list->str = NULL;
	list->flags = ft_strdup(".....");
	list->len = 0;
	list->prec = -1;
	list->conv = '\0';
	list->mod = 0;
	list->next = NULL;
	return (list);
}

void		ft_lst_addend(t_print **list, t_print *new)
{
	t_print		*tmp;

	tmp = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
