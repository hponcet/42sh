/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 19:14:48 by MrRobot           #+#    #+#             */
/*   Updated: 2016/06/28 10:51:40 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_error_4(int error, char *str)
{
	if (error == 15)
	{
		ft_putstr_fd("sh: Not a directory: ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
	}
}

static void	ft_error_3(int error, char *str)
{
	if (error == 9)
		ft_putstr_fd("sh: Parse error near separator.", g_shell.fd.stderr);
	else if (error == 10)
	{
		ft_putstr_fd("sh: Segmentation fault: ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
	}
	else if (error == 11)
	{
		ft_putstr_fd("\nsh: Terminated: ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
	}
	else if (error == 12)
		ft_putstr_fd("sh: Ambiguous redirect.", g_shell.fd.stderr);
	else if (error == 13)
		ft_putstr_fd("sh: Error no TERM variable", g_shell.fd.stderr);
	else if (error == 14)
	{
		ft_putstr_fd("sh: No set ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
	}
	else
		ft_error_4(error, str);
}

static void	ft_error_2(int error, char *str)
{
	if (error == 4)
	{
		ft_putstr_fd(str, g_shell.fd.stderr);
		ft_putstr_fd(": option requires an argument.", g_shell.fd.stderr);
	}
	else if (error == 5)
	{
		ft_putstr_fd("sh: no such file or directory: ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
	}
	else if (error == 6)
	{
		ft_putstr_fd("env: unsetenv ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
		ft_putstr_fd(": Invalid argument.", g_shell.fd.stderr);
	}
	else if (error == 7)
		ft_putstr_fd("setenv: Variable name contain '='.", g_shell.fd.stderr);
	else if (error == 8)
		ft_putstr_fd("sh: The file is not an executable.", g_shell.fd.stderr);
	else
		ft_error_3(error, str);
}

int			ft_error(int error, char *str)
{
	if (error == 0)
	{
		ft_putstr_fd("sh: command not found: ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
	}
	else if (error == 1)
	{
		ft_putstr_fd(str, g_shell.fd.stderr);
		ft_putstr_fd(" : can't change to home directory.", g_shell.fd.stderr);
	}
	else if (error == 2)
	{
		ft_putstr_fd("sh: permission denied: ", g_shell.fd.stderr);
		ft_putstr_fd(str, g_shell.fd.stderr);
	}
	if (error == 3)
	{
		ft_putstr_fd(str, g_shell.fd.stderr);
		ft_putstr_fd(": too many arguments.", g_shell.fd.stderr);
	}
	else
		ft_error_2(error, str);
	ft_putchar_fd('\n', g_shell.fd.fd);
	return (-1);
}
