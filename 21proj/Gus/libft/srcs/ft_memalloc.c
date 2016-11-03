/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:42:13 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/15 21:58:36 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	unsigned char	*buf;
	size_t			i;
	void			*ret;

	i = 0;
	buf = (void*)malloc(sizeof(unsigned char) * size);
	if (buf == NULL)
		return (NULL);
	while (i != size)
	{
		buf[i] = '\0';
		i++;
	}
	ret = (void*)buf;
	return (ret);
}
