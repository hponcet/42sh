/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 00:37:35 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 21:10:33 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_check(const char *format)
{
	int		format_len;
	t_print	*list;
	t_print	*tmp;

	tmp = NULL;
	list = NULL;
	format_len = ft_strlen(format);
	while (g_pi < format_len)
	{
		if ((tmp = ft_check_format(format)) != NULL)
			ft_lst_addend(&list, tmp);
		else
		{
			tmp = ft_check_arg(format);
			ft_lst_addend(&list, tmp);
		}
	}
	return (list);
}

t_print		*ft_check_arg_len(const char *format, t_print *list)
{
	while (format[g_pi] >= '0' && format[g_pi] <= '9')
	{
		list->len *= 10;
		list->len += format[g_pi] - 48;
		g_pi++;
	}
	return (list);
}

t_print		*ft_check_format(const char *format)
{
	t_print	*list;
	int		i;
	int		j;

	j = ft_check_next_perc(format);
	i = ft_cnindex((char*)format, '%', j);
	if (j != g_pi)
	{
		list = ft_lst_new();
		list->str = ft_strsub(format, j, g_pi - j);
		return (list);
	}
	else
		return (NULL);
}

t_print		*ft_check_arg(const char *format)
{
	t_print	*list;

	list = ft_lst_new();
	g_pi++;
	if (format[g_pi] == '#' || format[g_pi] == '-' || format[g_pi] == '+' ||
			format[g_pi] == '0' || format[g_pi] == ' ')
		list = ft_check_arg_flags(format, list);
	if (format[g_pi] >= '0' && format[g_pi] <= '9')
		list = ft_check_arg_len(format, list);
	if (format[g_pi] == '.')
	{
		g_pi++;
		list = ft_check_arg_prec(format, list);
	}
	if (format[g_pi] == 'l' || format[g_pi] == 'h' || format[g_pi] == 'j' ||
			format[g_pi] == 'z')
		list = ft_check_arg_mod(format, list);
	list = ft_check_arg_conv(format, list);
	return (list);
}
