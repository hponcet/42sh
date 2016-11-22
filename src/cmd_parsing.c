/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/22 15:50:02 by MrRobot          ###   ########.fr       */
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
	ft_back_quote(shell);
	shell->curs_pos = get_last_elem(shell->input);
	shell->input_len = lst_len(shell->input);
	cmd_str = lst_to_str(shell->input);
	shell->tree = store_cmd(cmd_str);
	free_tmp_inputs(shell, 1);
	if (check_btree(shell->tree) > 0)// jvoulais mettre ca aussi ds la fonction
	{							// du bas mais jsais pas si tu utilise le ret machin
		free_btree(shell->tree); // donc a toi de voir flav si tu met le if en bas
		return (ret);
	}
	ft_launch_cmd(shell, shell->tree);
	return (ret);
}

void	ft_launch_cmd(t_shell *shell, t_btree *tree)
{
	restore_term(shell);
	signal(SIGTSTP, SIG_DFL);
	handle_btree(shell, tree);
	free_btree(tree);
	shell->tree = NULL;
	reload_term(shell);
	signal(SIGTSTP, &sig_handler);
}
