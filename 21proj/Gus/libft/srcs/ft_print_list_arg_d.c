/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_arg_d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 04:59:48 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/15 18:49:01 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_list_arg_d(t_print *list, va_list ap)
{
	long long		i;
	char			*buf;

	i = ft_check_type(list, ap);
	buf = ft_itoa_base_ll(i, "0123456789", list);
	if (list->prec == 0 && i == 0)
		buf[0] = 0;
	ft_print_list_arg_d_flags(list, buf);
	free(buf);
}

void		ft_print_list_arg_d_flags(t_print *list, char *str)
{
	char	*buf;

	buf = NULL;
	if (list->prec >= (int)ft_strlen(str) && list->flags[1] != '-')
	{
		str = ft_nbr_prec(list, str);
		buf = ft_nbr_buf_len_prec(list, str);
		buf = ft_str_tools_wflags_char(buf, str, list);
	}
	else if (list->flags[1] == '-')
	{
		if (list->prec >= (int)ft_strlen(str))
			str = ft_nbr_prec(list, str);
		buf = ft_nbr_buf_len_prec(list, str);
		buf = ft_str_tools_mflags_char(buf, str, list);
	}
	else
	{
		buf = ft_nbr_buf_len_prec(list, str);
		buf = ft_str_tools_wflags_char(buf, str, list);
	}
	ft_str_buf_to_bufret(buf);
	free(buf);
}

char		*ft_nbr_prec(t_print *list, char *str)
{
	int		i;
	char	*buf;

	i = 0;
	if (str[0] < '0' || str[0] > '9')
		list->prec++;
	buf = ft_strnew(list->prec);
	while (i < list->prec)
	{
		buf[i] = '0';
		i++;
	}
	if (str[0] < '0' || str[0] > '9')
	{
		buf[0] = str[0];
		str = str + 1;
	}
	buf = ft_str_tools_wflags_char(buf, str, list);
	return (buf);
}

char		*ft_nbr_buf_esp(int j)
{
	int		i;
	char	*buf;

	buf = ft_strnew(j);
	i = 0;
	while (i < j)
	{
		buf[i] = ' ';
		i++;
	}
	return (buf);
}

void		ft_nbr_buf_zero(char *buf, char *str)
{
	int		i;

	i = -1;
	while (buf[++i] == ' ')
		buf[i] = '0';
	if (str[0] < '0' || str[0] > '9')
	{
		buf[0] = str[0];
		str = str + 1;
	}
}
