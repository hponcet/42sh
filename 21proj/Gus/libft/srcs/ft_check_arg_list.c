/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 04:20:19 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 21:09:19 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_check_arg_conv_2(const char *format, t_print *list)
{
	if (list->flags[3] == '0')
		list->str = ft_tools_buf_new_zero(list->len);
	else
		list->str = ft_nbr_buf_esp(list->len);
	if (list->flags[1] != '-')
		list->str[list->len - 1] = format[g_pi];
	else
		list->str[0] = format[g_pi];
}

t_print		*ft_check_arg_conv(const char *format, t_print *list)
{
	char	*err;

	err = NULL;
	if (format[g_pi] == 's' || format[g_pi] == 'S' || format[g_pi] == 'p' ||
			format[g_pi] == 'd' || format[g_pi] == 'D' || format[g_pi] == 'i' ||
			format[g_pi] == 'o' || format[g_pi] == 'O' || format[g_pi] == 'u' ||
			format[g_pi] == 'U' || format[g_pi] == 'x' || format[g_pi] == 'X' ||
			format[g_pi] == 'c' || format[g_pi] == 'C' || format[g_pi] == '%')
		list->conv = format[g_pi];
	else
	{
		if (list->len)
			ft_check_arg_conv_2(format, list);
		else
		{
			list->str = ft_strnew(1);
			list->str[0] = format[g_pi];
		}
	}
	g_pi++;
	return (list);
}

t_print		*ft_check_arg_flags(const char *format, t_print *list)
{
	while (format[g_pi] == '#' || format[g_pi] == '-' || format[g_pi] == '+' ||
			format[g_pi] == '0' || format[g_pi] == ' ')
	{
		if (format[g_pi] == '#')
			list->flags[0] = '#';
		if (format[g_pi] == '-')
			list->flags[1] = '-';
		if (format[g_pi] == '+')
			list->flags[2] = '+';
		if (format[g_pi] == '0')
			list->flags[3] = '0';
		if (format[g_pi] == ' ')
			list->flags[4] = ' ';
		g_pi++;
	}
	return (list);
}

t_print		*ft_check_arg_mod(const char *format, t_print *list)
{
	if (format[g_pi] == 'l' && format[++g_pi] != 'l')
		list->mod = 1;
	if (format[g_pi] == 'l')
	{
		list->mod = 2;
		g_pi++;
	}
	if (format[g_pi] == 'h' && format[++g_pi] != 'h')
		list->mod = 3;
	if (format[g_pi] == 'h')
	{
		list->mod = 4;
		g_pi++;
	}
	if (format[g_pi] == 'j' && format[++g_pi] != 'j')
		list->mod = 5;
	if (format[g_pi] == 'z' && format[++g_pi] != 'z')
		list->mod = 6;
	return (list);
}

t_print		*ft_check_arg_prec(const char *format, t_print *list)
{
	list->prec = 0;
	while (format[g_pi] >= '0' && format[g_pi] <= '9')
	{
		list->prec *= 10;
		list->prec += format[g_pi] - 48;
		g_pi++;
	}
	return (list);
}
