/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 18:59:56 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/21 15:50:48 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

//quote dans backquote

static t_input *ft_treat_back_quote(char *str, t_input **input, int *fd)
{
	char	**cmd;
	char	*path;

	
	//ouvrir fd, dup exec la commande dedans 
}



static char		*ft_lst_to_str_index(t_input *start, t_input *end)
{
	char	*cmd;
	int		i;

	i = 0;
	if (start->c == '`')
	{
		start = start->next;
		return (NULL);
	}
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

void	ft_back_quote(t_input **input, int *fd)
{
	t_input	*ptr;
	t_input	*tmp;
	char	*cmd;

	ptr = *input;
	while (ptr != NULL)
	{
		if (ptr->c == '`')
		{
			tmp = ptr->next;
			while (tmp->c != '`')
				tmp = tmp->next;
			cmd = ft_lst_to_str_index(ptr->next, tmp->prev);
			delete_input(input, ptr, NULL, 0);
			delete_input(input, tmp, NULL, 0);
			if (cmd == NULL)
				return ;
			ptr = ft_treat_back_quote(cmd, input, fd);
		}
		else
			ptr = ptr->next;
	}
}
