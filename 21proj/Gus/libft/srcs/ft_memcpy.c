/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 17:31:25 by hponcet           #+#    #+#             */
/*   Updated: 2015/11/30 16:01:11 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*d;

	t = (unsigned char*)src;
	d = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		d[i] = t[i];
		i++;
	}
	return (dst);
}
