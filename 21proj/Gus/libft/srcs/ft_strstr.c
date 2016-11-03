/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 17:50:22 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 23:53:52 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t		i;
	size_t		j;
	char		*ret;

	ret = (char*)big;
	i = 0;
	j = 0;
	if (little[i] == '\0')
		return (ret);
	while (big[i] != '\0')
	{
		while (little[j] == big[i + j] && big[i + j] != '\0')
			j++;
		if (little[j] == '\0')
			return (ret + i);
		i++;
		j = 0;
	}
	return (NULL);
}
