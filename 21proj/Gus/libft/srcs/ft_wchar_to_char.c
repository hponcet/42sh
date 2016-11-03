/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_to_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 22:16:54 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 20:36:30 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_wchar(wchar_t w)
{
	unsigned int	j;
	unsigned int	i;
	char			*tmp;
	char			*str;

	tmp = (char *)malloc(sizeof(char) * 33);
	ft_bzero((void *)tmp, 33);
	j = 31;
	i = (unsigned int)w;
	while (i > 0)
	{
		tmp[j] = (i % 2) + 48;
		i = i / 2;
		j--;
	}
	str = ft_wchar_complete(tmp);
	free(tmp);
	return (ft_wchar_conv_bit(str));
}

char	*ft_wchar_conv_bit(char *str)
{
	int		i;
	char	*buf;

	i = ft_strlen(str);
	if (i == 8)
	{
		buf = ft_strnew(1);
		ft_wchar_conv_bit1(str, 0, buf);
	}
	else if (i == 16)
	{
		buf = ft_strnew(2);
		ft_wchar_conv_bit2(str, 8, buf);
	}
	else if (i == 24)
	{
		buf = ft_strnew(3);
		ft_wchar_conv_bit3(str, 16, buf);
	}
	else
	{
		buf = ft_strnew(4);
		ft_wchar_conv_bit4(str, 24, buf);
	}
	return (buf);
}

char	*ft_wchar_complete(char *str)
{
	char	*abit;
	char	*bbit;
	char	*cbit;
	char	*dbit;

	ft_init_wchar_mask(&abit, &bbit, &cbit, &dbit);
	if (ft_wchar_octlen(str) <= 7)
	{
		ft_wchar_write(str, abit);
		return (abit);
	}
	else if (ft_wchar_octlen(str) <= 11)
	{
		ft_wchar_write(str, bbit);
		return (bbit);
	}
	else if (ft_wchar_octlen(str) <= 16)
	{
		ft_wchar_write(str, cbit);
		return (cbit);
	}
	else
		ft_wchar_write(str, dbit);
	return (dbit);
}

void	ft_wchar_write(char *str, char *mask)
{
	int i;
	int j;

	j = 31;
	i = ft_strlen(mask) - 1;
	while (i > 0)
	{
		if (mask[i] == 'x' && str[j] != '\0')
		{
			mask[i] = str[j];
			i--;
			j--;
		}
		else if (str[j] == '\0' && mask[i] == 'x')
		{
			mask[i] = '0';
			i--;
		}
		else if (mask[i] == '1' || mask[i] == '0')
			i--;
	}
}

int		ft_wchar_octlen(char *str)
{
	int i;
	int oct;

	i = 31;
	oct = 0;
	while (str[i] != 0)
	{
		i--;
		oct++;
	}
	return (oct);
}
