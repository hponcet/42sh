/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:59:56 by MrRobot           #+#    #+#             */
/*   Updated: 2016/12/07 16:34:13 by MrRobot          ###   ########.fr       */
/*   Updated: 2016/12/07 10:37:58 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_check_input(t_input *input)
{
	char	ret;

	ret = 0;
	if (check_separators(input, 1) == -1)
		return (1);
	if ((ret = valid_input(input)) != 0)
		return (ret == -1 ? 1 : cmd_error(0, ret, NULL));
	return (0);
}

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
	if (*curs != NULL && (*curs)->c == ' ')
		delete_input(&shell->input, *curs, NULL, 0);
}

static t_input	*ft_tbq(t_shell *shell, t_input **curs, char *str)
{
	t_btree	*tree;
	t_input	*input;
	int		fd;

	input = char_to_input(str);
	if (ft_check_input(input) != 0)
	{
		ft_strdel(&str);
		free_input_list(&input, NULL);
		return (NULL);
	}
	free_input_list(&input, NULL);
	fd = open("/tmp/back_quote.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	shell->fd[1] = fd;
	tree = store_cmd(str);
	if (ft_prepare_cmd(shell, tree) == 1)
		return (NULL);
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

int			ft_back_quote(t_shell *shell)
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
			cmd == NULL ? start = curs : (start = ft_tbq(shell, &curs, cmd));
		}
		else
			start = start->next;
	}
	return (0);
}
