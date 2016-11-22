/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_storage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 11:04:50 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/22 17:34:16 by hponcet          ###   ########.fr       */
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
	int	i;
	int	j;

	if (((i = strrchr_outside_quotes(ft_strdup(s), '&', 0)) > 0)
		&& (s[i - 1] == s[i]))
		;
	else
		i = -1;
	if (((j = strrchr_outside_quotes(ft_strdup(s), '|', 0)) > 0)
		&& (s[j - 1] == s[j]))
		;
	else
		j = -1;
	return (j > i ? j : i);
}

t_btree			*store_cmd(char *str)
{
	int		i;
	t_btree	*new;

	new = new_cmd_link();
	if ((i = strrchr_outside_quotes(ft_strdup(str), ';', 0)) != -1)
		new->type = SEM;
	else if ((i = strrchr_logical_op(str)) != -1)
		new->type = (str[i] == '&') ? AND : OR;
	else if ((i = strrchr_outside_quotes(ft_strdup(str), '|', 0)) != -1)
		new->type = PIP;
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
