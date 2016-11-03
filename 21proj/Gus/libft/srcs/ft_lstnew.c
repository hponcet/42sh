/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 17:58:51 by hponcet           #+#    #+#             */
/*   Updated: 2015/12/17 23:27:26 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	list = (t_list*)malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	if (content == NULL)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		list->content = malloc(content_size);
		if (list->content == NULL)
			return (NULL);
		ft_memcpy((list->content), content, content_size);
		list->content_size = content_size;
	}
	list->next = NULL;
	return (list);
}
