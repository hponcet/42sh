/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:46:00 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 19:13:55 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (i != n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
