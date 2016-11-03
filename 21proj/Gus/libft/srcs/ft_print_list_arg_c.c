/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_arg_c.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 18:13:14 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 18:54:33 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_list_arg_c(t_print *list, va_list ap)
{
	char	*buf;
	wchar_t	wchar;

	if (list->conv == 'c' && list->mod != 1)
	{
		buf = ft_strnew(1);
		buf[0] = (char)va_arg(ap, int);
		ft_print_list_arg_mins(list, buf);
		if (buf[0] == 0)
		{
			ft_lst_addend_nchar();
			g_null += 1;
		}
	}
	if (list->conv == 'C' || list->mod == 1)
	{
		wchar = (wchar_t)va_arg(ap, int);
		buf = ft_wchar(wchar);
		ft_print_list_arg_mins(list, buf);
		if (wchar == 0 && g_null++)
			ft_lst_addend_nchar();
	}
	free(buf);
}
