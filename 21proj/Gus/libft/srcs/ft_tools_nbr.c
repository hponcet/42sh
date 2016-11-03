/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:20:46 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 21:45:47 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_itoa_base_ll_neg(long long nbr, char *buf, t_print *list)
{
	int		t;

	t = 0;
	if (nbr < 0)
	{
		buf[t] = '-';
		t = 2;
	}
	else if (list->flags[2] == '+')
	{
		buf[t] = '+';
		t = 1;
	}
	else if (list->flags[4] == ' ')
	{
		buf[t] = ' ';
		t = 1;
	}
	return (t);
}

char		*ft_itoa_base_ll(long long nbr, char *base, t_print *list)
{
	int		r;
	long	i;
	int		t;
	long	len;
	char	*buf;

	t = nbr;
	buf = ft_strnew(21);
	len = ft_strlen(base);
	if ((t = ft_itoa_base_ll_neg(nbr, buf, list)) > 1)
		t = 1;
	i = 1;
	while ((nbr / i) >= len || (nbr / i) <= -len)
		i = i * len;
	while (i > 0)
	{
		r = nbr >= 0 ? (nbr / i) % len : -((nbr / i) % len);
		buf[t] = base[r];
		i = i / len;
		t++;
	}
	return (buf);
}

char		*ft_itoa_base_ul(unsigned long long nbr, char *base)
{
	int				r;
	size_t			i;
	int				t;
	unsigned long	len;
	char			*buf;

	t = nbr;
	buf = ft_strnew(20);
	len = ft_strlen(base);
	i = 1;
	while ((nbr / i) >= len)
		i = i * len;
	t = 0;
	while (i > 0)
	{
		r = (nbr / i) % len;
		buf[t] = base[r];
		i = i / len;
		t++;
	}
	return (buf);
}

int			ft_countnbr(int nb)
{
	size_t		i;

	i = 1;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

long		ft_power(long nb, long power)
{
	long i;
	long res;

	i = 1;
	res = nb;
	if (power == 0)
		return (1);
	while (i < power)
	{
		res = res * nb;
		i++;
	}
	return (res);
}
