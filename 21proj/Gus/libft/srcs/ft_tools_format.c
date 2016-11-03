/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 01:26:38 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 20:49:32 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_cnindex(char *str, char c, int i)
{
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] != c)
		return (-1);
	return (i);
}

int		ft_check_next_perc(const char *format)
{
	int		i;

	i = g_pi;
	while (format[g_pi] != '\0')
	{
		if (format[g_pi] == '%' && format[g_pi + 1] != '%')
			return (i);
		if (format[g_pi] == '%' && format[g_pi + 1] == '%')
			g_pi++;
		g_pi++;
	}
	return (i);
}
