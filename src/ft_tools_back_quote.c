/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:04:33 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/21 19:48:24 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t	ft_list_size_index(t_input *start, t_input *end)
{
	size_t size;

	size = 0;
	while (start != end->next)
	{
		start = start->next;
		size++;
	}
	return (size);
}

void	ft_lst_del(t_shell *shell, t_input *start, t_input *end)
{
	t_input	*tmp;

	while (start != end)
	{
		tmp = start->next;
		delete_input(&shell->input, start, NULL, 0);
		start = tmp;
	}
	delete_input(&shell->input, start, NULL, 0);
}

t_input	*ft_new_link(char c)
{
	t_input *new;

	new = malloc(sizeof(t_input));
	new->c = c;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
