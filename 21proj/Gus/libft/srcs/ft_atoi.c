/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 17:57:58 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/13 20:16:18 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	n;
	int				i;
	int				csign;

	i = 0;
	n = 0;
	csign = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i]
		== ' ' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		csign = i;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	if (str[csign] == '-')
		n = -n;
	return (n);
}
