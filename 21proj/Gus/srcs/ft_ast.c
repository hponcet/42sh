/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 01:20:22 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 18:57:35 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_ast(char *cmd)
{
	char	*cmd1;
	char	*cmd2;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (cmd[len])
	{
		if (cmd[len] == '|')
			j = len;
		len++;
	}
	cmd1 = ft_strsub(cmd, 0, j);
	cmd2 = ft_strsub(cmd, j + 1, (ft_strlen(cmd) - j));
	ft_strdel(&cmd);
	ft_pipe(cmd1, cmd2);
	ft_strdel(&cmd1);
	ft_strdel(&cmd2);
}

void		ft_pipe(char *cmd1, char *cmd2)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	status = 0;
	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		ms_exec(cmd2, g_curs.env);
		waitpid(-2, &status, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ms_exec(cmd1, g_curs.env);
	}
	exit(0);
}
