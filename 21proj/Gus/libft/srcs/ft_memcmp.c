/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:22:25 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 19:27:59 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	while (n > 0)
	{
		if (str1[i] != str2[i])
			return ((str1[i]) - (str2[i]));
		if (str1[i] == str2[i])
		{
			i++;
			n--;
		}
	}
	return (0);
}
