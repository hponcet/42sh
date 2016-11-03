/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 21:09:06 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 23:54:42 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*ret;

	ret = (char*)big;
	i = 0;
	j = 0;
	if (little[i] == '\0')
		return (ret);
	while (big[i] != '\0' && i < len)
	{
		while (little[j] == big[i + j] && big[i + j] != '\0' && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return (ret + i);
		i++;
		j = 0;
	}
	return (NULL);
}
