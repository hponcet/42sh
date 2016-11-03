/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrvrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 17:36:32 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/18 20:12:16 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrvrs(char *str)
{
	int			i;
	size_t		j;
	char		*ret;

	j = 0;
	i = ft_strlen(str) - 1;
	ret = ft_strnew(i + 1);
	while (i > -1)
	{
		ret[j] = str[i];
		i--;
		j++;
	}
	return (ret);
}
