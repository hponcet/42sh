/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:59:54 by MrRobot           #+#    #+#             */
/*   Updated: 2016/09/26 11:04:53 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_fork(char **tab, char *path, t_list *env)
{
	char	**environ;
	int		sig;
	pid_t	father;

	environ = ft_list_in_env(env);
	father = fork();
	if (father == 0)
	{
		ft_dup_fd(&g_shell.fd);
		if (ft_check_builtins(&env, tab) == -1)
			if (execve(path, tab, environ) == -1)
				ft_error(8, NULL);
		exit(EXIT_SUCCESS);
	}
	else if (father > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&sig);
		ft_close_fd(&g_shell.fd);
		if (WIFEXITED(sig) == 0)
			ft_signal_2(sig, path);
		ft_free_tab(environ);
		free(path);
	}
}

void	ft_no_fork(char *str, t_list **env)
{
	char			**tmp;
	char			**cmd;
	char			**environ;
	char			*path;

	tmp = ft_strsplit_space(str);
	if (tmp[0] == NULL)
		ft_error(12, NULL);
	cmd = ft_remove_quote_tab(tmp);
	path = ft_set_path(cmd, *env);
	environ = ft_list_in_env(*env);
	if (path != NULL && ft_check_builtins(env, cmd) == -1)
	{
		if (execve(path, cmd, environ) == -1)
			ft_error(8, NULL);
	}
	ft_free_tab(environ);
	ft_free_tab(tmp);
	ft_free_tab(cmd);
	free(path);
	exit(EXIT_SUCCESS);
}
