/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 18:49:33 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/11 19:51:42 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	replace_backslash(char **s, int i)
{
	char	*tmp;

	tmp = ft_replace_str(*s, i, 1, "");
	free(*s);
	*s = tmp;
	if (*s[i] == '\\' || *s[i] == '$')
		return (1);
	return (0);
}

int	replace_tilde(char **s, int i)
{
	char	*tmp;
	t_env	*home;
	t_shell *shell;

	shell = get_struct(0);
	home = get_env_ptr(shell->env_lst, "HOME");
	if (!home || !home->val[0])
		return (1);
	tmp = ft_replace_str(*s, i, 1, home->val);
	free(*s);
	*s = tmp;
	return (i + ft_strlen(home->val));
}
