/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 04:44:06 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/16 22:01:45 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_str_buf_len_prec(t_print *list, char *str)
{
	char	*buf;

	if (list->len > list->prec && list->prec != -1)
		buf = ft_str_tools_len_char(list->len);
	else if (list->len >= (int)ft_strlen(str))
		buf = ft_str_tools_len_char(list->len);
	else if (list->len <= list->prec && list->prec > (int)ft_strlen(str))
		buf = ft_str_tools_len_char(ft_strlen(str));
	else if (list->len <= list->prec && list->prec != -1 && list->prec <
			(int)ft_strlen(str) && (list->conv == 's' || list->conv == 'S'))
		buf = ft_str_tools_len_char(list->prec);
	else if (list->prec < (int)ft_strlen(str) && list->prec != -1 &&
			(list->conv == 's' || list->conv == 'S'))
		buf = ft_str_tools_len_char(list->prec);
	else
		buf = ft_str_tools_len_char(ft_strlen(str));
	return (buf);
}

char		*ft_nbr_buf_len_prec(t_print *list, char *str)
{
	char	*buf;

	if (list->len >= (int)ft_strlen(str))
		buf = ft_str_tools_len_char(list->len);
	else
		buf = ft_str_tools_len_char(ft_strlen(str));
	if (list->flags[3] == '0' && list->prec < 0 && list->flags[1] != '-')
		ft_nbr_buf_zero(buf, str);
	return (buf);
}

void		ft_str_buf_to_bufret(char *buf)
{
	char		*tmp;

	tmp = ft_strdup(g_bufret);
	ft_strdel(&g_bufret);
	g_bufret = ft_strjoin(tmp, buf);
	ft_strdel(&tmp);
}

char		*ft_tools_buf_new_zero(int i)
{
	int		j;
	char	*buf;

	j = 0;
	buf = ft_strnew(i);
	while (j < i)
	{
		buf[j] = '0';
		j++;
	}
	return (buf);
}
