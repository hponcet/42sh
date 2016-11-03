/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:45:36 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 23:58:23 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*buf;

	i = 0;
	if (s != NULL && f != NULL)
	{
		buf = ft_strnew(ft_strlen(s));
		if (!buf)
			return (NULL);
		while (i != ft_strlen(s))
		{
			buf[i] = f(i, s[i]);
			i++;
		}
		return (buf);
	}
	return (NULL);
}
