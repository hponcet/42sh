/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_flags_ht.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 01:46:20 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/17 08:04:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_print_list_flags_ht_x(t_print *list, char *buf)
{
	char	*htbuf;

	if (buf[0] == '0' && buf[1] == '0')
	{
		if (list->conv == 'x')
			buf[1] = 'x';
		if (list->conv == 'X')
			buf[1] = 'X';
		return (buf);
	}
	htbuf = ft_strnew(ft_strlen(buf) + 2);
	htbuf[0] = '0';
	if (list->conv == 'x')
		htbuf[1] = 'x';
	if (list->conv == 'X')
		htbuf[1] = 'X';
	htbuf = ft_strcat(htbuf, buf);
	free(buf);
	return (htbuf);
}

char	*ft_print_list_flags_ht_o(t_print *list, char *buf)
{
	char	*htbuf;

	list->str = NULL;
	htbuf = ft_strnew(ft_strlen(buf) + 1);
	htbuf[0] = '0';
	if (buf)
		htbuf = ft_strcat(htbuf, buf);
	free(buf);
	return (htbuf);
}
