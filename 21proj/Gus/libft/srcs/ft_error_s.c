/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 06:34:43 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/16 23:31:17 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_error_mins(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 's');
	if (list->flags[2] == '+')
		ft_error_flags('+', 's');
	if (list->flags[4] == ' ')
		ft_error_flags(' ', 's');
	if (list->flags[3] == '0')
		ft_error_flags('0', 's');
	if (list->mod == 1)
		ft_error_len(1, 's');
	if (list->mod == 2)
		ft_error_len(2, 's');
	if (list->mod == 3)
		ft_error_len(3, 's');
	if (list->mod == 4)
		ft_error_len(4, 's');
	if (list->mod == 5)
		ft_error_len(5, 's');
	if (list->mod == 6)
		ft_error_len(6, 's');
}

void	ft_error_majs(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 'S');
	if (list->flags[2] == '+')
		ft_error_flags('+', 'S');
	if (list->flags[4] == ' ')
		ft_error_flags(' ', 'S');
	if (list->flags[3] == '0')
		ft_error_flags('0', 'S');
	if (list->prec != -1)
		ft_error_conv('S');
	if (list->mod == 1)
		ft_error_len(1, 'S');
	if (list->mod == 2)
		ft_error_len(2, 'S');
	if (list->mod == 3)
		ft_error_len(3, 'S');
	if (list->mod == 4)
		ft_error_len(4, 'S');
	if (list->mod == 5)
		ft_error_len(5, 'S');
	if (list->mod == 6)
		ft_error_len(6, 'S');
}
