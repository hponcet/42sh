/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 20:57:31 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/26 20:44:12 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	store_buffer(t_input **buf, char c)
{
	t_input	*new;
	t_input	*tmp;

	if (!(new = (t_input *)malloc(sizeof(*new))))
		ft_put_error(ER_MEM, 1);
	new->c = c;
	new->next = NULL;
	if (!(*buf))
	{
		new->prev = NULL;
		*buf = new;
	}
	else
	{
		tmp = *buf;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

int		paste_buffer(t_shell *shell)
{
	t_input *tmp;
	t_input *pos_save;

	if (!shell->buffer)
		return (-1);
	tmp = shell->buffer;
	pos_save = shell->curs_pos;
	signal(SIGINT, SIG_IGN);
	while (tmp)
	{
		store_input(shell, tmp->c);
		tmp = tmp->next;
	}
	pos_save = pos_save ? pos_save->next : shell->input;
	print_input(shell, pos_save, shell->p_len);
	return (0);
}
