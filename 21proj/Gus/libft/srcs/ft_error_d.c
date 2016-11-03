/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:11:48 by hponcet           #+#    #+#             */
/*   Updated: 2016/03/16 09:24:02 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_error_mind(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 'd');
}

void	ft_error_majd(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 'D');
}

void	ft_error_i(t_print *list)
{
	if (list->flags[0] == '#')
		ft_error_flags('#', 'i');
}
