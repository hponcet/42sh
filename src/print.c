/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 18:19:07 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/26 19:24:47 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			putchar(int c)
{
	t_shell	*shell;

	shell = get_struct(0);
	write(shell->fd[3], &c, 1);
	return (0);
}

static void	print_eol(t_shell *shell, char *buf, size_t p_len, int overflow)
{
	t_input *tmp;
	int		i;

	i = 0;
	tmp = overflow ? shell->input : shell->curs_pos;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (((shell->input_len + p_len) % shell->col) == 0 && i--)
	{
		ft_putstr_fd(buf, shell->fd[1]);
		tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
		replace_cursor(shell, 42, 1);
	}
	else
		ft_putstr_fd(buf, shell->fd[1]);
	if (overflow)
	{
		tputs(tgetstr("rc", NULL), shell->fd[3], &putchar);
		replace_cursor(shell, 1, 0);
	}
	else
	{
		while (--i)
			replace_cursor(shell, 1, 1);
	}
}

static void	clear_and_print(t_shell *shell, t_input *curs_pos, size_t p_len)
{
	int		i;
	int		overflow;
	char	buf[shell->input_len + 1];
	t_input	*tmp;

	i = 0;
	overflow = 0;
	ft_bzero((void *)buf, shell->input_len + 1);
	if ((lst_len(shell->curs_pos) + shell->col) >= shell->winsize)
	{
		overflow++;
		tmp = shell->input;
		tputs(tgetstr("sc", NULL), shell->fd[3], &putchar);
		tputs(tgetstr("cl", NULL), shell->fd[3], &putchar);
		print_prompt(shell, 0);
	}
	else
	{
		tmp = curs_pos;
		tputs(tgetstr("cd", NULL), shell->fd[3], &putchar);
	}
	while (tmp && (buf[i++] = tmp->c))
		tmp = tmp->next;
	print_eol(shell, buf, p_len, overflow);
}

void		print_input(t_shell *shell, t_input *curs_pos, size_t p_len)
{
	if (!curs_pos->next &&
		((get_cursor_x_pos(shell->input, curs_pos, p_len) % shell->col) == 0))
	{
		ft_putchar_fd(curs_pos->c, shell->fd[1]);
		tputs(tgetstr("do", NULL), shell->fd[3], &putchar);
	}
	else if (!curs_pos->next)
		ft_putchar_fd(curs_pos->c, shell->fd[1]);
	else
		clear_and_print(shell, curs_pos, p_len);
}
