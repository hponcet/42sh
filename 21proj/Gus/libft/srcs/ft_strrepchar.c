/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 17:03:54 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/18 17:37:32 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrepchar(char *str, char c, char newc)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = newc;
		i++;
	}
	return (str);
}
