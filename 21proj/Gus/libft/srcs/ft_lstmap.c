/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 18:00:28 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 19:30:20 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*nlist;
	t_list	*begin_list;

	if (lst != NULL)
		nlist = f(lst);
	else
		return (NULL);
	lst = lst->next;
	begin_list = nlist;
	while (lst != NULL)
	{
		nlist->next = f(lst);
		lst = lst->next;
		nlist = nlist->next;
	}
	return (begin_list);
}
