/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 13:41:32 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 13:41:48 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		get_fd(void)
{
	char	*ttypath;

	ttypath = ttyname(3);
	if (!ttypath)
		ttypath = ttyname(1);
	if (!ttypath)
		ttypath = ttyname(0);
	if (!ttypath)
		ttypath = ttyname(2);
	if (!ttypath)
		return ;
	g_curs.fd = open(ttypath, O_RDWR | O_NOCTTY);
	free(ttypath);
	if (g_curs.fd == -1)
		return ;
}
