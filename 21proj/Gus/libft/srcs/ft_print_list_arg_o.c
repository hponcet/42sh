/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_arg_o.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 21:12:17 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 20:53:19 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_list_arg_o(t_print *list, va_list ap)
{
	unsigned long long	ln;
	char				*buf;
	char				*tmp;

	buf = NULL;
	ln = ft_check_utype(list, ap);
	ln = ft_check_umod_error(list, ln);
	if (ln == 0 && list->prec == 0)
		buf = ft_strnew(0);
	else
		buf = ft_itoa_base_ul(ln, "01234567");
	if (list->prec > (int)ft_strlen(buf) || (list->flags[3] == '0' &&
		list->len > (int)ft_strlen(buf) && list->flags[1] != '-'))
	{
		tmp = ft_print_list_arg_x_prec(list, buf);
		free(buf);
		buf = tmp;
	}
	ft_print_list_arg_mins(list, buf);
}
