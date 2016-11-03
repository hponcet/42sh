/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:45:26 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 23:57:14 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t		i;
	char		*buf;

	i = 0;
	if (s != NULL && f != NULL)
	{
		buf = ft_strnew(ft_strlen(s));
		if (!buf)
			return (NULL);
		while (i != ft_strlen(s))
		{
			buf[i] = f(s[i]);
			i++;
		}
		return (buf);
	}
	return (NULL);
}
