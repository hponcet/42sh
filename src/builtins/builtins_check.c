/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 17:51:56 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/24 20:02:05 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "history") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv") ||
		!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "read"))
		return (1);
	return (0);
}
