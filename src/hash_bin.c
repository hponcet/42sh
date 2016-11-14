/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 21:45:34 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/14 17:19:40 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_hash		**hash_bin(t_shell *shell)
{
	t_hash	**htbl;
	char	**paths;
	int		i;

	i = 0;
	if (!(paths = compl_pathbin(shell)))
		return (NULL);
	htbl = hash_newtbl(HASHLEN);
	while (paths[i])
	{
		hash_addpath(htbl, paths[i], HASHLEN);
		i++;
	}
	free_tab(paths);
	return (htbl);
}
