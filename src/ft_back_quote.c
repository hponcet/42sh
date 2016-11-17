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

void	ft_back_quote(t_input **input)
{
	char	*cmd;
	t_input	*ptr;
	t_input	*tmp

	ptr = *input;
	while (ptr->c != NULL)
	{
		if (ptr->c == '`')
		{
			tmp = ptr->next;
			while (tmp->c != '`')
				tmp = tmp->next;
			ptr = ft_treat_back_quote(ptr->next, tmp->prev);
		}
		else
			ptr = ptr->next;
	}
}

//quote dans backquote
//

void	ft_treat_back_quote(t_input *start, t_intput *tmp)
{
	
}
