/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 17:51:56 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/15 02:33:42 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "history") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv") ||
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
