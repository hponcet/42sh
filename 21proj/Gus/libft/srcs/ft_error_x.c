/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 17:21:00 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/16 23:35:24 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_error_minx(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 's');
	if (list->flags[2] == '+')
		ft_error_flags('+', 's');
	if (list->flags[4] == ' ')
		ft_error_flags(' ', 's');
}
