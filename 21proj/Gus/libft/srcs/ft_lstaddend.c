/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 17:59:47 by hponcet           #+#    #+#             */
/*   Updated: 2016/04/15 00:05:49 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
