/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:58:58 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/29 21:25:07 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		export_error(int errnum, char *arg)
{
	int	fd;

	fd = STDERR_FILENO;
	if (errnum == 0)
	{
		ft_putstr_fd("export: illegal option -- ", fd);
		ft_putstr_fd(++arg, fd);
	}
	ft_putstr_fd("\nusage: export [-p] [name[=value]]...\n", fd);
	return (1);
}
