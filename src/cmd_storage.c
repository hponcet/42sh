/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_storage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 11:04:50 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/24 16:04:29 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_btree	*new_cmd_link(void)
{
	t_btree	*new;

	if (!(new = (t_btree *)malloc(sizeof(*new))))
		ft_put_error(ER_MEM, 1);
	new->str = NULL;
	new->redir = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

static int		strrchr_logical_op(char *s)
{
	int		i;
	char	c;

	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		if (ft_isquote(s[i]) && (c = s[i--]))
		{
			while (i > 0 && s[i] != c)
				i--;
		}
		else if ((s[i] == '|' || s[i] == '&') && s[i - 1] == s[i])
			return (i);
		if (i > 0)
			i--;
	}
	return (-1);
}

t_btree			*store_cmd(char *str)
{
	int		i;
	t_btree	*new;

	new = new_cmd_link();
	if ((i = strrchr_outside_quotes(str, ';')) != -1)
		new->type = SEM;
	else if ((i = strrchr_logical_op(str)) != -1)
		new->type = (str[i] == '&') ? AND : OR;
	else if ((i = strrchr_outside_quotes(str, '|')) != -1)
	{
		new->type = PIP;
	}
	if (i != -1 && ++i)
	{
		if (new->type == AND || new->type == OR)
			new->left = store_cmd(ft_strsub(str, 0, i - 2));
		else
			new->left = store_cmd(ft_strsub(str, 0, i - 1));
		new->right = store_cmd(ft_strsub(str, i, (ft_strlen(str) - i)));
		free(str);
	}
	else
	{
		new->type = CMD;
		ft_glob(&str);
		new->str = str;
	}
	return (new);
}
