/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:50:19 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 23:46:49 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *restrict dst, const void *restrict src,
int c, size_t n)
{
	unsigned char	*s;
	unsigned char	chr;
	size_t			i;
	unsigned char	*d;
	void			*ret;

	s = (unsigned char*)src;
	chr = (unsigned char)c;
	d = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		if (chr == s[i])
		{
			i++;
			ret = dst + i;
			return (ret);
		}
		i++;
	}
	return (0);
}
