/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:59:56 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/24 15:42:39 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_output_insert(t_shell *shell, t_input **curs, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		i = 0;
		while (line[i] != 0)
		{
			if (*curs == NULL)
			{
				shell->input = ft_new_link(line[i]);
				*curs = shell->input;
			}
			else
				ft_input_add(curs, line[i]);
			i++;
		}
		ft_strdel(&line);
		ft_input_add(curs, ' ');
	}
}

static t_input	*ft_treat_back_quote(t_shell *shell, t_input **curs, char *str)
{
	t_btree	*tree;
	int		fd;

	/// check parsing
	fd = open("/tmp/back_quote.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	shell->fd[1] = fd;
	tree = store_cmd(str);
	ft_launch_cmd(shell, tree);
	close(fd);
	close_and_reset_fd(shell->fd);
	fd = open("/tmp/back_quote.txt", O_RDONLY);
	ft_output_insert(shell, curs, fd);
	close(fd);
	return (*curs);
}

static char		*ft_lst_to_str_index(t_input *start, t_input *end)
{
	char	*cmd;
	int		i;

	i = 0;
	if (start->c == '`')
		return (NULL);
	cmd = ft_strnew(ft_list_size_index(start, end));
	while (start != end)
	{
		cmd[i] = start->c;
		start = start->next;
		i++;
	}
	cmd[i] = start->c;
	return (cmd);
}

void	ft_back_quote(t_shell *shell)
{
	t_input	*start;
	t_input	*end;
	t_input	*curs;
	char	*cmd;

	start = shell->input;
	while (start != NULL)
	{
		if (start->c == '`')
		{
			end = start->next;
			while (end->c != '`')
				end = end->next;
			start->prev != NULL ? (curs = start->prev) : (curs = end->next);
			cmd = ft_lst_to_str_index(start->next, end->prev);
			ft_lst_del(shell, start, end);
			if (cmd == NULL)
				return ;
			start = ft_treat_back_quote(shell, &curs, cmd);
		}
		else
			start = start->next;
	}
}
