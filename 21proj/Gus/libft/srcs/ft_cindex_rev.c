/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cindex_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 02:39:13 by hponcet           #+#    #+#             */
/*   Updated: 2016/06/03 03:28:54 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cindex_rev(char *str, char c)
{
	int		len;

	if (!str)
		return (-1);
	len = ft_strlen(str) - 1;
	while (len > -1 && str[len] != c)
		len--;
	return (len);
}
