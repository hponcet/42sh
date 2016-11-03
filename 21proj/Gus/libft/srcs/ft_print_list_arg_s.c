/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prin_list_arg_s.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 03:48:23 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/16 21:33:41 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_list_arg_s(t_print *list, va_list ap)
{
	char			*buf;
	wchar_t			*wbuf;

	buf = NULL;
	wbuf = NULL;
	if (list->conv == 'S' || list->mod == 1)
	{
		wbuf = (wchar_t *)va_arg(ap, int *);
		if (!wbuf)
			ft_arg_s_ret_null();
		else
			ft_print_list_arg_majs(list, wbuf);
	}
	else
	{
		buf = va_arg(ap, char *);
		if (!buf)
			ft_arg_s_ret_null();
		else
			ft_print_list_arg_mins(list, buf);
	}
}

char		*ft_print_list_arg_mins_ht(t_print *list, char *buf)
{
	if (list->flags[0] == '#' && (list->conv == 'x' || list->conv == 'X'))
		buf = ft_print_list_flags_ht_x(list, buf);
	if (list->flags[0] == '#' && (list->conv == 'o' || list->conv == 'O'))
		buf = ft_print_list_flags_ht_o(list, buf);
	return (buf);
}

void		ft_print_list_arg_mins(t_print *list, char *str)
{
	char	*buf;

	if ((str[0] == '0' && str[1] == '\0') || (str[0] == '\0' && list->conv !=
				'o' && list->conv != 'O'))
		;
	else
		str = ft_print_list_arg_mins_ht(list, str);
	buf = ft_str_buf_len_prec(list, str);
	if (list->flags[1] == '-')
		buf = ft_str_tools_mflags_char(buf, str, list);
	else
		buf = ft_str_tools_wflags_char(buf, str, list);
	if ((list->conv == 'c' || list->conv == 'C') && list->len != 0 &&
			str[0] == 0)
	{
		free(buf);
		if (list->flags[3] != '0')
			buf = ft_str_tools_len_char(list->len);
		if (list->flags[3] == '0')
			buf = ft_tools_buf_new_zero(list->len);
		buf[list->len - 1] = 0;
	}
	ft_str_buf_to_bufret(buf);
	free(buf);
}

void		ft_print_list_arg_majs(t_print *list, wchar_t *wstr)
{
	int			i;
	char		*tmp;
	char		*tmp2;
	char		*nbr;

	i = 0;
	nbr = NULL;
	if (!wstr[i])
		return ;
	while (wstr[i])
	{
		tmp = ft_wchar(wstr[i]);
		if (nbr)
		{
			tmp2 = nbr;
			nbr = ft_strjoin(tmp2, tmp);
			free(tmp2);
		}
		else
			nbr = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	ft_print_list_arg_mins(list, nbr);
}
