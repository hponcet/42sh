/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 10:52:39 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/16 15:34:49 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		common_error(int errnum, char *value)
{
	int		fd;

	fd = STDERR_FILENO;
	if (errnum == 1)
		ft_putstr_fd("42sh: unable to open history file\n", fd);
	if (errnum == 2)
		ft_putstr_fd("42sh: Environnement variable $PATH not found\n", fd);
	if (errnum == 3)
		ft_putstr_fd("42sh: Environnement variable $HOME not found\n", fd);
	if (value)
		free(value);
	return (1);
}

void	quit_error(int errnum)
{
	int		fd;

	fd = STDERR_FILENO;
	if (errnum == 1)
		ft_putstr_fd("42sh: unable to open the terminal device file\n", fd);
	else if (errnum == 2)
		ft_putstr_fd("42sh: no entry found for the specified terminal\n", fd);
	else if (errnum == 3)
		ft_putstr_fd("42sh: unable to find the terminfo database\n", fd);
	else if (errnum == 4)
		ft_putstr_fd("42sh: unable to retrieve the terminal parameters\n", fd);
	else if (errnum == 5)
		ft_putstr_fd("tcsetattr: unable to set the terminal parameters\n", fd);
	else if (errnum == 6)
		ft_putstr_fd("malloc: memory allocation has failed\n", fd);
	else if (errnum == 7)
		ft_putstr_fd("read: an error occured while reading the input\n", fd);
	else if (errnum == 8)
		ft_putstr_fd("42sh: terminal capabilities not supported\n", fd);
	else if (errnum == 9)
		ft_putstr_fd("42sh: memory allocation has failed\n", fd);
	else if (errnum == 10)
		ft_putstr_fd("ioctl: unable to get the terminal state infos\n", fd);
	exit(EXIT_FAILURE);
}

int		exec_error(int errnum, char *arg)
{
	int		fd;
	t_shell	*shell;

	fd = STDERR_FILENO;
	shell = get_struct(0);
	ft_putstr_fd("42sh: ", fd);
	ft_putstr_fd(arg, fd);
	if (errnum == 0)
		ft_putstr_fd(": error on child process creation\n", fd);
	else if (errnum == 1 && (shell->status = 127))
		ft_putstr_fd(": command not found\n", fd);
	else if (errnum == 2)
		ft_putstr_fd("environment variable PATH is not set or is empty\n", fd);
	else if (errnum == 3 && (shell->status = 126))
		ft_putstr_fd(": permission denied\n", fd);
	else if (errnum == 4)
		ft_putstr_fd(": error on child process execution\n", fd);
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
