/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 21:28:30 by MrRobot           #+#    #+#             */
/*   Updated: 2016/08/29 11:19:59 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_cd_less(t_list *env)
{
	char	*pwd;
	char	*dir;

	if ((pwd = ft_return_path("PWD", env)) == NULL)
		return (ft_error(14, "PWD"));
	if ((dir = ft_return_path("OLDPWD", env)) == NULL)
	{
		free(pwd);
		return (ft_error(14, "OLDPWD"));
	}
	ft_change_path("PWD", dir, env);
	ft_change_path("OLDPWD", pwd, env);
	if (access(dir, F_OK) == -1)
		ft_error(5, dir);
	else if (access(dir, X_OK) == -1)
		ft_error(2, dir);
	else if (chdir(dir) == -1)
		ft_error(5, dir);
	free(pwd);
	free(dir);
	return (1);
}

static int	ft_check_path_cd(t_list *env, char **tab)
{
	char		*tmp;
	struct stat	info;
	int			i;

	i = 1;
	if (tab[i][0] == '~')
		tab[i] = ft_treat_tilde(tab[i]);
	if (lstat(tab[i], &info) == -1)
		return (ft_error(5, tab[i]));
	else if (S_ISREG(info.st_mode) == 1)
		return (ft_error(15, tab[i]));
	else if (access(tab[i], X_OK) == -1)
		return (ft_error(2, tab[i]));
	chdir(tab[i]);
	tmp = ft_return_path("PWD", env);
	ft_change_path("OLDPWD", tmp, env);
	free(tmp);
	tmp = getcwd(NULL, MAXPATHLEN);
	ft_change_path("PWD", tmp, env);
	free(tmp);
	return (1);
}

static int	ft_parsing_cd(t_list *env, char **tab)
{
	int	i;

	i = 1;
	if (tab[i] == NULL)
		return (-1);
	else if (tab[i + 1] != NULL)
	{
		ft_error(3, tab[0]);
		return (0);
	}
	else if (ft_strcmp(tab[i], "-") == 0)
		ft_cd_less(env);
	else
		ft_check_path_cd(env, tab);
	return (1);
}

int			ft_cd(t_list *env, char **tab)
{
	char	*tmp;

	if (ft_parsing_cd(env, tab) == -1)
	{
		if ((tmp = ft_return_path("HOME", env)) == NULL)
			return (ft_error(1, tab[0]));
		else if (access(tmp, X_OK) == -1)
		{
			free(tmp);
			return (ft_error(2, tmp));
		}
		free(tmp);
		tmp = ft_return_path("PWD", env);
		ft_change_path("OLDPWD", tmp, env);
		free(tmp);
		tmp = ft_return_path("HOME", env);
		ft_change_path("PWD", tmp, env);
		chdir(tmp);
		free(tmp);
	}
	return (1);
}
