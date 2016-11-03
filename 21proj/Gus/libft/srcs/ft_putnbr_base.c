/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 19:23:11 by hponcet           #+#    #+#             */
/*   Updated: 2016/04/15 00:04:29 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(long int nbr, char *base)
{
	int	r;
	int	i;
	int	len;

	len = ft_strlen(base);
	i = 1;
	while ((nbr / i) >= len)
		i = i * len;
	while (i > 0)
	{
		r = (nbr / i) % len;
		ft_putchar(base[r]);
		i = i / len;
	}
}
