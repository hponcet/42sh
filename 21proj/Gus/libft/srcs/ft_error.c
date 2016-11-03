/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 07:52:37 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 21:01:54 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_error(t_print *list)
{
	while (list)
	{
		if (list->conv == 's')
			ft_error_mins(list);
		if (list->conv == 'S')
			ft_error_majs(list);
		if (list->conv == 'u')
			ft_error_minu(list);
		if (list->conv == 'U')
			ft_error_maju(list);
		if (list->conv == 'd')
			ft_error_mind(list);
		if (list->conv == 'D')
			ft_error_majd(list);
		if (list->conv == 'i')
			ft_error_i(list);
		list = list->next;
	}
}

void	ft_error_flags(char c, char conv)
{
	ft_putstr("error: flag \'");
	ft_putchar(c);
	ft_putstr("\' results in undefined behavior with \'");
	ft_putchar(conv);
	ft_putendl("\' conversion specifier");
	exit(0);
}

void	ft_error_len(int len, char conv)
{
	ft_putstr("error: length modifier \'");
	if (len == 1)
		ft_putchar('l');
	if (len == 2)
		ft_putstr("ll");
	if (len == 3)
		ft_putchar('h');
	if (len == 4)
		ft_putstr("hh");
	if (len == 5)
		ft_putchar('j');
	if (len == 6)
		ft_putchar('z');
	ft_putstr("\' results in undefined behavior or no effect with \'");
	ft_putchar(conv);
	ft_putendl("\' conversion specifier");
	exit(0);
}

void	ft_error_conv(char conv)
{
	ft_putstr("error: precision used with \'");
	ft_putchar(conv);
	ft_putendl("\'conversion specifier, resulting in undefined behavior");
	exit(0);
}
