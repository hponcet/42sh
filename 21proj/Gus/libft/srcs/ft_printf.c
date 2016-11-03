/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:37:57 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/16 22:03:02 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_del_checklist(t_print *list)
{
	t_print	*tmp;

	while (list)
	{
		tmp = list;
		free(list->str);
		free(list->flags);
		list = list->next;
		free(tmp);
	}
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_print		*list;

	va_start(ap, format);
	list = ft_check(format);
	ft_print(list, ap);
	va_end(ap);
	ft_del_checklist(list);
	ft_strdel(&g_bufret);
	return (g_lenret);
}
