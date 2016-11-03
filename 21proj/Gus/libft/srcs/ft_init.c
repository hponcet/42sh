/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 03:09:45 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 20:59:41 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_g(void)
{
	g_bufret = ft_strnew(0);
	g_lenret = 0;
	g_pi = 0;
	g_null = 0;
	g_lastindex = 0;
}

void	ft_init_wchar_mask(char **abit, char **bbit, char **cbit, char **dbit)
{
	*abit = ft_strdup("0xxxxxxx");
	*bbit = ft_strdup("110xxxxx10xxxxxx");
	*cbit = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	*dbit = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx");
}
