/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 07:54:24 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/16 09:12:06 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_error_minu(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 'u');
	if (list->flags[2] == '+')
		ft_error_flags('+', 'u');
	if (list->flags[4] == ' ')
		ft_error_flags(' ', 'u');
}

void	ft_error_maju(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 'U');
	if (list->flags[2] == '+')
		ft_error_flags('+', 'U');
	if (list->flags[4] == ' ')
		ft_error_flags(' ', 'U');
}
