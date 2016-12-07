/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:04:33 by MrRobot           #+#    #+#             */
/*   Updated: 2016/12/07 16:48:30 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_prepare_cmd(t_shell *shell, t_btree *tree)
{
	t_env	*new_env;
	t_env	*tmp;
	int		ret;

	tmp = shell->env_lst;
	new_env = NULL;
	dup_env_lst(shell->env_lst, &new_env);
	shell->env_lst = new_env;
	ret = ft_launch_cmd(shell, tree);
	free_env_lst(&shell->env_lst);
	shell->env_lst = tmp;
	return (ret);
}

size_t	ft_list_size_index(t_input *start, t_input *end)
{
	size_t size;

	size = 0;
	while (start != end)
	{
		start = start->next;
		size++;
	}
	size++;
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

void	ft_input_add(t_input **curs, char c)
{
	t_input	*new;

	new = ft_new_link(c);
	new->prev = *curs;
	new->next = (*curs)->next;
	if ((*curs)->next != NULL)
		(*curs)->next->prev = new;
	(*curs)->next = new;
	*curs = (*curs)->next;
}
