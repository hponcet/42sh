/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 16:52:18 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/08 17:09:38 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		chr;
	int			i;
	char		*ret;

	i = ft_strlen(s);
	chr = (char)c;
	ret = (char*)s;
	while (i != -1)
	{
		if (chr == s[i])
			return (ret + i);
		i--;
	}
	return (NULL);
}
