/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:13:19 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/30 21:33:12 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		**parse_cmd(t_env *env_lst, t_btree *link)
{
	int		i;
	char	*tmp;
	char	**cmd_tab;

	i = 0;
	tmp = remove_cmd_redir(ft_strtrim(link->str), link->redir);
	free(link->str);
	link->str = tmp;
	if (!(cmd_tab = strsplit_args(link->str)) || !cmd_tab[0])
		return (NULL);
	while (cmd_tab[i])
	{
		if (i == 0 && (strchr_outside_quotes(cmd_tab[i], '=') != -1)
			&& (set_local_variable(env_lst, &cmd_tab[i]) == 0))
			{
				tmp = *cmd_tab;
				cmd_tab++;
				free(tmp);
				if (!(cmd_tab[0]))
					return (NULL);
				continue;
			}
		else
			cmd_tab[i] = interpret_cmd_arg(cmd_tab[i]);
		i++;
	}
	return (cmd_tab);
}

int			handle_input(t_shell *shell)
{
	int		ret;
	char	*cmd_str;

	cmd_str = NULL;
	move_line_end(shell);
	tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
	if ((ret = check_input(shell)) > 0)
		return (ret);
	if (!(hist_checkdouble(shell)))
		shell->hist = store_hist(shell);
	if (ft_back_quote(shell) != 0)
	{
		free_tmp_inputs(shell, 1);
		return (0);
	}
	shell->curs_pos = get_last_elem(shell->input);
	shell->input_len = lst_len(shell->input);
	cmd_str = lst_to_str(shell->input);
	shell->tree = store_cmd(cmd_str);
	free_tmp_inputs(shell, 1);
	ft_launch_cmd(shell, shell->tree);
	return (0);
}

int		ft_launch_cmd(t_shell *shell, t_btree *tree)
{
	if (check_btree(tree) > 0)
	{
		free_btree(tree);
		return (1);
	}
	restore_term(shell);
	signal(SIGTSTP, SIG_DFL);
	handle_btree(shell, tree);
	free_btree(tree);
	shell->tree = NULL;
	reload_term(shell);
	signal(SIGTSTP, &sig_handler);
	return (0);
}
