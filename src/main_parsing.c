/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 17:50:57 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/21 17:17:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_input_form(t_shell *shell)
{
	char			c;
	t_input			*tmp;

	c = 0;
	if (shell->input_save)
	{
		shell->input_len += lst_len(shell->input_save);
		tmp = get_last_elem(shell->input_save);
		tmp->next = shell->input;
		if (shell->input)
			shell->input->prev = tmp;
		shell->input = shell->input_save;
	}
	if ((c = valid_input(shell->input, c)) > 0)
	{
		c == '\\' ? delete_input(&(shell->input), shell->curs_pos, shell, 0)
		: store_input(shell, '\n');
		shell->input_save = shell->input;
		shell->input = NULL;
		shell->input_len = 0;
		shell->curs_pos = NULL;
	}
	else
		shell->input_save = NULL;
	return ((int)c);
}

static int	free_and_return(t_shell *shell, int ret)
{
	if (ret == 0)
		free_tmp_inputs(shell, 1);
	else
		free_tmp_inputs(shell, 0);
	return (ret);
}

int			check_input(t_shell *shell)
{
	int		ret;

	ret = 1;
	if (!shell->input && !shell->input_save)
		return (ret);
	if ((check_separator(shell->input, '|', 1) == -1) && cmd_error(0, '|', NULL))
		return (free_and_return(shell, ret));
	if (((ret = check_input_form(shell)) > 0) || lst_is_empty(shell->input))
		return (free_and_return(shell, ret));
	return (0);
}

int			check_btree(t_btree *link)
{
	if (link->type != CMD)
	{
		if (link->left && check_btree(link->left) > 0)
			return (1);
		if (link->right && check_btree(link->right) > 0)
			return (1);
	}
	else if ((strchr_redir(link)) == -1)
		return (1);
	return (0);
}
