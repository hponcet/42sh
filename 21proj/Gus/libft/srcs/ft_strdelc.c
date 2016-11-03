/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 13:32:10 by hponcet           #+#    #+#             */
/*   Updated: 2016/04/06 13:48:57 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdelc(char *str, int i)
{
	char	*tmp;
	int		j;
	int		k;

	k = 0;
	j = 0;
	if (i < 0 || !str)
		return (str);
	tmp = (char*)malloc(sizeof(char) * ft_strlen(str));
	tmp[ft_strlen(str)] = '\0';
	while (str[k])
	{
		if (k == i)
			k++;
		tmp[j] = str[k];
		j++;
		k++;
	}
	return (tmp);
}
