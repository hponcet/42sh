/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 16:40:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/13 12:38:13 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		compl_addstrend(t_shell *shell, char *str, int type)
{
	int		i;

	i = 0;
	while (str[i])
	{
		store_input(shell, str[i]);
		ft_putchar(str[i++]);
	}
	if (type == 1)
	{
		store_input(shell, '/');
		ft_putchar('/');
	}
	else if (type == 0)
	{
		store_input(shell, ' ');
		ft_putchar(' ');
	}
}

void		compl_addstr(t_shell *shell, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		store_input(shell, str[i]);
		ft_putchar(str[i++]);
	}
}

int			compl_retstr(t_compl *tmp, t_shell *shell, int pos, int i)
{
	tputs(tgetstr("rc", 0), 1, putchar);
	tputs(tgetstr("ce", 0), 1, putchar);
	if (i == 1)
		compl_addstrend(shell, tmp->name + pos, tmp->type);
	else
		compl_addstr(shell, tmp->name + pos);
	return (1);
}

int			compl_retstrchar(t_compl *tmp, t_shell *shell, int pos, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = tmp->name + pos;
	tputs(tgetstr("rc", 0), 1, putchar);
	tputs(tgetstr("ce", 0), 1, putchar);
	compl_addstr(shell, str);
	store_input(shell, c);
	ft_putchar(c);
	return (1);
}
