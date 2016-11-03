/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 21:10:39 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/18 22:01:01 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nmatch(char *str1, char *str2)
{
	if (!*str1 && !*str2)
		return (1);
	else if (*str2 == '*' && *str2 && *str1)
		return (nmatch(str1, str2 + 1) + nmatch(str1 + 1, str2));
	else if (*str1 == *str2 && *str1 != '*')
		return (nmatch(str1 + 1, str2 + 1));
	else if (*str2 == '*' && !*str1)
		return (nmatch(str1, str2 + 1));
	else if (*str1 == '*' && *str2 == '*')
		return (nmatch(str1 + 1, str2));
	else
		return (0);
}
