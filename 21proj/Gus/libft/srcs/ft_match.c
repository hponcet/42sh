/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:23:42 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 19:08:50 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		match(char *str1, char *str2)
{
	if (*str1 && *str2 == '*')
		return (match(str1 + 1, str2) || match(str1, str2 + 1));
	else if (!*str1 && *str2 == '*')
		return (match(str1, str2 + 1));
	else if (*str1 == *str2 && *str1 && *str2)
		return (match(str1 + 1, str2 + 1));
	else if (!*str1 && !*str2)
		return (1);
	return (0);
}
