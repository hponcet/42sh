/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_arg_pc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 00:19:27 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/20 20:52:38 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_list_arg_pc(t_print *list)
{
	char	*buf;

	if (list->flags[3] == '0')
	{
		buf = ft_tools_buf_new_zero(list->len);
		buf[list->len - 1] = list->conv;
	}
	else
	{
		if (list->len > 1)
		{
			buf = ft_nbr_buf_esp(list->len);
			if (list->flags[1] != '-')
				buf[list->len - 1] = list->conv;
			else
				buf[0] = list->conv;
		}
		else
		{
			buf = ft_strnew(1);
			buf[0] = list->conv;
		}
	}
	ft_print_list_arg_mins(list, buf);
}
