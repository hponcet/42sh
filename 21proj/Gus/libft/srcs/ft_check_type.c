/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 22:30:20 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 21:10:06 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long		ft_check_utype(t_print *list, va_list ap)
{
	unsigned long long	i;

	if (list->mod == 1 || list->conv == 'U' || list->conv == 'O')
		i = va_arg(ap, unsigned long);
	else if (list->mod == 2)
		i = va_arg(ap, unsigned long long);
	else if (list->mod == 3)
		i = (unsigned short)va_arg(ap, unsigned int);
	else if (list->mod == 4)
		i = (unsigned char)va_arg(ap, unsigned int);
	else if (list->mod == 5)
		i = va_arg(ap, uintmax_t);
	else if (list->mod == 6)
		i = va_arg(ap, ssize_t);
	else
		i = va_arg(ap, unsigned int);
	return (i);
}

long long				ft_check_type(t_print *list, va_list ap)
{
	long long	i;

	if (list->mod == 1 || list->conv == 'D')
		i = va_arg(ap, long);
	else if (list->mod == 2)
		i = va_arg(ap, long long);
	else if (list->mod == 3)
		i = (short)va_arg(ap, int);
	else if (list->mod == 4)
		i = (char)va_arg(ap, int);
	else if (list->mod == 5)
		i = va_arg(ap, intmax_t);
	else if (list->mod == 6)
		i = va_arg(ap, size_t);
	else
		i = va_arg(ap, int);
	return (i);
}
