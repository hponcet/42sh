/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 12:32:30 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/15 22:28:26 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*buf;
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char*)src;
	d = (unsigned char*)dst;
	if (n < 1)
		return (dst);
	i = 0;
	buf = (unsigned char *)malloc(sizeof(*buf) * n);
	while (i < n)
	{
		buf[i] = s[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		d[i] = buf[i];
		i++;
	}
	free(buf);
	buf = NULL;
	return (dst);
}
