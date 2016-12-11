/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 18:19:07 by fkoehler          #+#    #+#             */
/*   Updated: 2016/12/11 17:23:32 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			putchar(int c)
{
	t_shell	*shell;

	shell = get_struct(0);
	write(shell->fd[3], &c, 1);
	return (0);
}
