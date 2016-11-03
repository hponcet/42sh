/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compl_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 16:40:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/22 16:42:12 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_compl_addstrend(char *str, int type)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_chain_addchar(str[i++]);
		ft_init_pos();
		ft_count_chain();
	}
	if (type == 1)
		ft_chain_addchar('/');
	else if (type == 0)
		ft_chain_addchar(' ');
}

void		ft_compl_addstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_chain_addchar(str[i++]);
		ft_init_pos();
		ft_count_chain();
	}
}

int			ft_compl_retstr(t_compl *tmp, char *find, int *pos, int i)
{
	tputs(tgoto(tgetstr("cm", 0), pos[0] - 1, pos[1] - 1), 1, ft_char);
	tputs(tgetstr("ce", 0), 1, ft_char);
	if (i == 1)
		ft_compl_addstrend(tmp->name + ft_strlen(find), tmp->type);
	else
		ft_compl_addstr(tmp->name + ft_strlen(find));
	return (1);
}

int			ft_compl_retstrchar(t_compl *tmp, char *find, int *pos, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = tmp->name + ft_strlen(find);
	tputs(tgoto(tgetstr("cm", 0), pos[0] - 1, pos[1] - 1), 1, ft_char);
	tputs(tgetstr("ce", 0), 1, ft_char);
	ft_compl_addstr(str);
	ft_chain_addchar(c);
	ft_init_pos();
	ft_count_chain();
	return (1);
}
