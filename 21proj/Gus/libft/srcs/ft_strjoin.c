/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:46:29 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/16 21:57:20 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = NULL;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	buf = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	while (s1[i])
		buf[j++] = s1[i++];
	i = 0;
	while (s2[i])
		buf[j++] = s2[i++];
	return (buf);
}
