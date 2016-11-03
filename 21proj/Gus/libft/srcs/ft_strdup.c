/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:51:30 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 23:52:48 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*buf;
	int		i;

	i = 0;
	buf = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!buf)
		return (NULL);
	while (s1[i] != '\0')
	{
		buf[i] = s1[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
