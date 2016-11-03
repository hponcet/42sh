/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 15:56:36 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/08 16:41:05 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		chr;
	size_t		i;
	char		*ret;

	i = 0;
	chr = (char)c;
	ret = (char*)s;
	while (s[i] != '\0')
	{
		if (chr == s[i])
			return (ret + i);
		i++;
	}
	if (chr == '\0')
		return (ret + i);
	else
		return (NULL);
}
