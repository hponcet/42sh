/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 11:18:02 by MrRobot           #+#    #+#             */
/*   Updated: 2016/08/29 11:18:03 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_treat_tilde(char *str)
{
	char	*tmp;
	char	*tmp_2;
	char	*path;

	tmp = ft_strsub(str, 1, ft_strlen(str) - 1);
	free(str);
	tmp_2 = ft_return_path("HOME", g_shell.env);
	path = ft_strjoin(tmp_2, tmp);
	free(tmp);
	free(tmp_2);
	return (path);
}
