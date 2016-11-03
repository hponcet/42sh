/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:42:39 by hponcet           #+#    #+#             */
/*   Updated: 2016/04/15 00:03:20 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *str, int len)
{
	char	*nstr;
	int		i;

	i = 0;
	if ((size_t)len >= ft_strlen(str))
		return (str);
	if (!(nstr = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1))))
		return (NULL);
	ft_bzero(nstr, (ft_strlen(str) - len + 1));
	while (str[i])
	{
		nstr[i] = str[i + len];
		i++;
	}
	if (str)
		free(str);
	str = NULL;
	return (nstr);
}
