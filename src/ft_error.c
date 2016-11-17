/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:39:14 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/17 15:59:46 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_put_error(char *error, int action)
{
	int fd;

	fd = STDERR_FILENO;
	ft_putstr_fd(error, fd);
	if (action == 1)
		exit(EXIT_FAILURE);
	return (1);
}

int		exec_error(int errnum, char *arg)
{
	int		fd;
	t_shell	*shell;

	fd = STDERR_FILENO;
	shell = get_struct(0);
	ft_putstr_fd("42sh: ", fd);
	ft_putstr_fd(arg, fd);
	shell->status = 1;
	if (errnum == 0)
		ft_putstr_fd(": error on child process creation\n", fd);
	else if (errnum == 1 && (shell->status = 127))
		ft_putstr_fd(": command not found\n", fd);
	else if (errnum == 2)
		ft_putstr_fd("environment variable PATH is not set or is empty\n", fd);
	else if (errnum == 3 && (shell->status = 126))
		ft_putstr_fd(": permission denied\n", fd);
	else if (errnum == 4)
		ft_putstr_fd(": command too long\n", fd);
	else if (errnum == 5)
		ft_putstr_fd("error on pipe creation\n", fd);
	else if (errnum == 6)
		ft_putstr_fd(": error on file descriptor duplication\n", fd);
	else if (errnum == 7)
		ft_putstr_fd(": error on file descriptor closure\n", fd);
	else if (errnum == 8)
		ft_putstr_fd("error on file creation/opening\n", fd);
	return (-1);
}

int		cmd_error(int errnum, char c, char *s)
{
	int		fd;

	fd = STDERR_FILENO;
	if (errnum == 0)
	{
		ft_putstr_fd("42sh: parse error near '", fd);
		ft_putchar_fd(c, fd);
		ft_putstr_fd("'\n", fd);
	}
	else if (errnum == 1)
		ft_putstr_fd("42sh: bad file descriptor\n", fd);
	else if (errnum == 2)
	{
		ft_putstr_fd("42sh: ", fd);
		ft_putstr_fd(s, fd);
		ft_putstr_fd(": ambigous redirect\n", fd);
	}
	return (-1);
}
