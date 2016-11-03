/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 02:11:06 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 22:49:20 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print(t_print *list, va_list ap)
{
	ft_init_g();
	while (list)
	{
		if (list->str)
			ft_print_list_str(list);
		else
			ft_print_list_arg(list, ap);
		list = list->next;
	}
	if (g_null > 0)
		ft_putstr_nchar(g_bufret);
	else
		ft_putstr(g_bufret);
	g_lenret = ft_strlen(g_bufret) + g_null;
}

void		ft_print_list_arg(t_print *list, va_list ap)
{
	if (list->conv == 's' || list->conv == 'S')
		ft_print_list_arg_s(list, ap);
	if (list->conv == 'c' || list->conv == 'C')
		ft_print_list_arg_c(list, ap);
	if (list->conv == 'o' || list->conv == 'O')
		ft_print_list_arg_o(list, ap);
	if (list->conv == 'u' || list->conv == 'U')
		ft_print_list_arg_u(list, ap);
	if (list->conv == 'd' || list->conv == 'D' || list->conv == 'i')
		ft_print_list_arg_d(list, ap);
	if (list->conv == 'x' || list->conv == 'X')
		ft_print_list_arg_x(list, ap);
	if (list->conv == 'p')
		ft_print_list_arg_p(list, ap);
	if (list->conv == '%')
		ft_print_list_arg_pc(list);
}
