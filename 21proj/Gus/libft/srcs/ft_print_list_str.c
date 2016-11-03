/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 03:07:29 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 18:32:41 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_list_str(t_print *list)
{
	char	*buf;
	int		i;
	int		j;

	buf = ft_strnew(ft_strlen(list->str));
	i = 0;
	j = 0;
	while (list->str[i])
	{
		if (list->str[i] == '%')
			i++;
		if (list->str[i] == 92)
		{
			buf[j] = ft_print_list_str_escseq(list->str[++i]);
			i++;
		}
		buf[j] = list->str[i];
		i++;
		j++;
	}
	ft_str_buf_to_bufret(buf);
	free(buf);
}

char		ft_print_list_str_escseq(char c)
{
	if (c == 'n')
		return (10);
	else if (c == 't')
		return (9);
	else if (c == 'v')
		return (11);
	else if (c == 'f')
		return (12);
	else if (c == 'b')
		return (8);
	else if (c == 'r')
		return (13);
	else
	{
		ft_putstr("error: unknown escape sequence '");
		ft_putchar(92);
		ft_putchar(c);
		ft_putendl("'");
		exit(0);
	}
	return (0);
}
