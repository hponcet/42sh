/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 00:52:16 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/08 01:12:25 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*ft_join_tab(char **tb)
{
	char	*ret;
	int		i;
	int		j;
	int		totlen;

	i = 0;
	j = 0;
	totlen = 0;
	while (tb[i])
		totlen += ft_strlen(tb[i++]);
	ret = ft_strnew(totlen + i);
	i = 0;
	totlen = 0;
	while (tb[i])
	{
		while (tb[i][j])
			ret[totlen++] = tb[i][j++];
		if (tb[i + 1])
			ret[totlen++] = ' ';
		i++;
		j = 0;
	}
	return (ret);
}
