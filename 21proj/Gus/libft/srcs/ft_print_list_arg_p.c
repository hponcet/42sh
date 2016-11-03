/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_arg_p.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 02:35:45 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/19 08:29:33 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_list_arg_p(t_print *list, va_list ap)
{
	unsigned long	i;
	char			*tmp;
	char			*buf;
	char			*tmp2;

	i = (unsigned long)va_arg(ap, void *);
	tmp = ft_itoa_base_ul(i, "0123456789abcdef");
	if (i == 0 && list->prec == 0)
		tmp = ft_strnew(0);
	if (list->prec > 0 && list->prec > (int)ft_strlen(tmp))
	{
		tmp2 = ft_tools_buf_new_zero(list->prec - ft_strlen(tmp));
		tmp = ft_strjoin(tmp2, tmp);
		free(tmp2);
	}
	buf = ft_strnew(ft_strlen(tmp) + 2);
	buf[0] = '0';
	buf[1] = 'x';
	buf = ft_strcat(buf, tmp);
	free(tmp);
	ft_print_list_arg_mins(list, buf);
}
