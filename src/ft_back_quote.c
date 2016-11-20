/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:59:56 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/17 19:46:50 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//quote dans backquote
/*
static void	ft_treat_back_quote(char *cmd, t_input **input, int *fd)
{
	
}
*/

static size_t	ft_list_size_index(t_input *start, t_input *end)
{
	size_t size;

	size = 0;
	while (start != NULL && start != end->next)
	{
		start = start->next;
		size++;
	}
	return (size);
}

static char		*ft_lst_to_str_index(t_input **start, t_input *end)
{
	char	*cmd;
	int		i;

	if ((*start)->c == '`')
	{
		*start = (*start)->next;
		return (NULL);
	}
	cmd = ft_strnew(ft_list_size_index(*start, end));
	i = 0;
	while (*start != end)
	{
		cmd[i] = (*start)->c;
		*start = (*start)->next;
		i++;
	}
	cmd[i] = (*start)->c;
	return (cmd);
}

void	ft_back_quote(t_input **input, int *fd)
{
	t_input	*ptr;
	t_input	*tmp;
	char	*cmd;

	int i;
	i =fd[1];
	ptr = *input;
	while (ptr != NULL)
	{
		if (ptr->c == '`')
		{
			tmp = ptr->next;
			while (tmp->c != '`')
				tmp = tmp->next;
			cmd = ft_lst_to_str_index(&ptr->next, tmp->prev);
			if (cmd != NULL)
				ft_putstr(cmd);
		//	if (cmd != NULL)
		//		ft_treat_back_quote(cmd, input, fd);
			ptr = tmp->next;
		}
		else
			ptr = ptr->next;
	}
}
