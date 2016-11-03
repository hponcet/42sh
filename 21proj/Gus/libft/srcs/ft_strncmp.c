/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 21:52:29 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/18 17:38:11 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				ret;
	unsigned char	*ucs1;
	unsigned char	*ucs2;

	ucs1 = (unsigned char*)s1;
	ucs2 = (unsigned char*)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ucs1[i] == ucs2[i] && i < n)
	{
		if ((ucs1[i] == '\0' && ucs2[i] == '\0') || (i == n - 1 &&
ucs1[i] == ucs2[i]))
			return (0);
		i++;
	}
	ret = (int)ucs1[i] - (int)ucs2[i];
	return (ret);
}
