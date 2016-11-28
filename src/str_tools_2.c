/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:16:34 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/25 16:17:08 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	is_chr_escaped(char const *s, int i)
{
	int	backslash;

	backslash = 0;
	while (--i >= 0 && s[i] == '\\')
		backslash++;
	return (backslash % 2);
}
