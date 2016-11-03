/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 07:24:49 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/25 18:36:05 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_minishell.h"

void		ms_exec(char *cmd, char **env)
{
	char	*testbin;

	testbin = NULL;
	env = ms_builtin_cd(env);
	if (g_cmd)
		env = ms_search_builtin_env(cmd, env);
	if (g_cmd && g_cmd[0][0] == '.' && ms_get_point() < 1)
		return ;
	if (g_cmd && g_cmd[0][0] != '/' && g_cmd[0][0] != '~' && (g_curs.opt->htbl)
			&& !(testbin = ft_hash_search(g_curs.hash_bin, g_cmd[0],
			__HTBL_LEN__)))
	{
		ft_printf("21sh: Command not found: %s\n", g_cmd[0]);
		ft_strdel(&testbin);
		return ;
	}
	if (g_i == 0)
		ms_exec_fork(cmd, env);
	g_i = 0;
	ft_strdel(&testbin);
}

void		ms_exec_fork(char *cmd, char **env)
{
	pid_t	pid;
	int		status;
	char	*pathbin;

	pathbin = NULL;
	status = 0;
	if (!g_cmd)
		return ;
	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		if (ft_cindex_noquote(cmd, '|') > 1)
			ft_ast(cmd);
		ft_redir_exec(cmd);
		pathbin = ms_search_bin(env);
		ms_exec_bin(pathbin, env);
		ft_strdel(&pathbin);
		exit(0);
	}
}

void		ms_exec_bin(char *pathbin, char **env)
{
	if (!pathbin)
		exit(0);
	execve(pathbin, g_cmd, env);
}
