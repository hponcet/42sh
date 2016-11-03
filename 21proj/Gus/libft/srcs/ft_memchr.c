/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:09:46 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/15 21:59:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;
	size_t			i;
	void			*ret;

	i = 0;
	chr = (unsigned char)c;
	str = (unsigned char*)s;
	while (i < n)
	{
		if (chr == str[i])
		{
			ret = (void*)s;
			return (ret + i);
		}
		if (chr != str[i])
			i++;
	}
	return (NULL);
}
