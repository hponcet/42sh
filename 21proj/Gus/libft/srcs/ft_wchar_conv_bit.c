/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_conv_bit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 00:33:23 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/15 02:12:07 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_wchar_conv_bit1(char *str, int i, char *buf)
{
	int	p;
	int wchar;

	wchar = 0;
	p = 7;
	while (i < 8)
	{
		if (str[i] == '0')
			p--;
		else
		{
			wchar = wchar + (ft_power(2, p));
			p--;
		}
		i++;
	}
	buf[0] = wchar;
}

void	ft_wchar_conv_bit2(char *str, int i, char *buf)
{
	int	p;
	int wchar;

	wchar = 0;
	p = 7;
	ft_wchar_conv_bit1(str, 0, buf);
	while (i < 16)
	{
		if (str[i] == '0')
			p--;
		else
		{
			wchar = wchar + (ft_power(2, p));
			p--;
		}
		i++;
	}
	buf[1] = wchar;
}

void	ft_wchar_conv_bit3(char *str, int i, char *buf)
{
	int	p;
	int wchar;

	wchar = 0;
	p = 7;
	ft_wchar_conv_bit2(str, 8, buf);
	while (i < 24)
	{
		if (str[i] == '0')
			p--;
		else
		{
			wchar = wchar + (ft_power(2, p));
			p--;
		}
		i++;
	}
	buf[2] = wchar;
}

void	ft_wchar_conv_bit4(char *str, int i, char *buf)
{
	int	p;
	int wchar;

	wchar = 0;
	p = 7;
	ft_wchar_conv_bit3(str, 16, buf);
	while (i < 32)
	{
		if (str[i] == '0')
			p--;
		else
		{
			wchar = wchar + (ft_power(2, p));
			p--;
		}
		i++;
	}
	buf[3] = wchar;
}
