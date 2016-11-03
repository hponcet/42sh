/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_arg_x.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 02:04:13 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 20:51:15 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_print_list_arg_x(t_print *list, va_list ap)
{
	unsigned long	ln;
	char			*buf;
	char			*tmp;

	buf = NULL;
	ln = ft_check_utype(list, ap);
	ln = ft_check_umod_error(list, ln);
	if (ln == 0 && list->prec == 0)
		buf = ft_strnew(0);
	if (list->conv == 'x' && buf == NULL)
		buf = ft_itoa_base_ul(ln, "0123456789abcdef");
	if (list->conv == 'X' && buf == NULL)
		buf = ft_itoa_base_ul(ln, "0123456789ABCDEF");
	if (list->prec > (int)ft_strlen(buf) || (list->flags[3] == '0' &&
		list->len > (int)ft_strlen(buf) && list->flags[1] != '-'))
	{
		tmp = ft_print_list_arg_x_prec(list, buf);
		free(buf);
		buf = tmp;
	}
	ft_print_list_arg_mins(list, buf);
}

char				*ft_print_list_arg_x_prec(t_print *list, char *str)
{
	char	*buf;
	int		i;
	int		j;

	if (list->flags[3] == '0' && list->flags[1] != '-')
	{
		j = list->len - 1;
		buf = ft_tools_buf_new_zero(list->len);
	}
	else
	{
		buf = ft_tools_buf_new_zero(list->prec);
		j = list->prec - 1;
	}
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		buf[j] = str[i];
		i--;
		j--;
	}
	return (buf);
}

unsigned long long	ft_check_umod_error(t_print *list, unsigned long long i)
{
	if (list->mod == 0 && i > UINT64_MAX)
		return (0);
	if (list->mod == 1 && i > ULONG_MAX)
		return (0);
	if (list->mod == 2 && i > ULONG_MAX)
		return (0);
	if (list->mod == 3 && i > USHRT_MAX)
		return (0);
	if (list->mod == 4 && i > USHRT_MAX)
		return (0);
	if (list->mod == 5 && i > UINT64_MAX)
		return (0);
	if (list->mod == 6 && i > UINT64_MAX)
		return (0);
	return (i);
}
