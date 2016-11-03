/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:46:13 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 21:25:30 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*buf;
	size_t		j;

	j = 0;
	buf = ft_strnew(len);
	i = (size_t)start + len;
	if (s == NULL || buf == NULL)
		return (NULL);
	while (start < i)
	{
		buf[j] = s[start];
		start++;
		j++;
	}
	return (buf);
}
