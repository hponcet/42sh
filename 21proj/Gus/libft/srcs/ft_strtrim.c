/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 17:58:31 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/16 20:05:07 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int			i;
	int			j;

	j = 0;
	if (s == NULL)
		return (NULL);
	i = ft_strlen(s) - 1;
	while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
		j++;
	if (s[j] == '\0')
		return (ft_strnew(0));
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	return (ft_strsub(s, j, i - j + 1));
}
