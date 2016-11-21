/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/21 18:50:23 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		**parse_cmd(t_btree *link)
{
	int		i;
	char	*tmp;
	char	**cmd_tab;

	i = 0;
	tmp = remove_cmd_redir(ft_strtrim(link->str), link->redir);
	free(link->str);
	link->str = tmp;
	cmd_tab = strsplit_args(link->str);
	if (!cmd_tab[0])
	{
		free_tab(cmd_tab);
		return (NULL);
	}
	while (cmd_tab[i])
	{
		cmd_tab[i] = interpret_cmd_arg(cmd_tab[i]);
		i++;
	}
	return (cmd_tab);
}

int			handle_input(t_shell *shell)
{
	int		ret;
	char	*cmd_str;

	ret = 0;
	cmd_str = NULL;
	move_line_end(shell);
	tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
	if ((ret = check_input(shell)) > 0)
		return (ret);
	if (!(hist_checkdouble(shell))) // if pour checker les doublons dans l'historique
		shell->hist = store_hist(shell);
	// back quote
	cmd_str = lst_to_str(shell->input);
	shell->tree = store_cmd(cmd_str);
	free_tmp_inputs(shell, 1);
	if (check_btree(shell->tree) > 0)
	{
		free_btree(shell->tree);
		return (ret);
	}
	restore_term(shell);
	signal(SIGTSTP, SIG_DFL);
	handle_btree(shell, shell->tree);
	free_btree(shell->tree);
	shell->tree = NULL;
	reload_term(shell);
	signal(SIGTSTP, &sig_handler);
	return (ret);
}
