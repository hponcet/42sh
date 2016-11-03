/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_arg_u.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 03:11:59 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 18:51:01 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_list_arg_u(t_print *list, va_list ap)
{
	unsigned long	ln;
	char			*buf;

	ln = ft_check_utype(list, ap);
	buf = ft_itoa_base_ul(ln, "0123456789");
	if (list->prec == 0 && ln == 0)
		buf[0] = 0;
	ft_print_list_arg_d_flags(list, buf);
	free(buf);
}
