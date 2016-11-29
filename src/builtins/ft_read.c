/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:44:55 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/29 21:32:46 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_treat_read(char **argv, char **split, t_env **env, int start)
{
	char	*tmp;
	t_env	*var;
	int		i;

	i = 0;
	while (split[i] != NULL)
	{
		if (argv[start] == NULL)
		{
			tmp = ft_strjoin(var->val, split[i]);
			free(var->val);
			var->val = tmp;
		}
		else if ((var = get_env_ptr(*env, argv[start])) != NULL)
		{
			free(var->val);
			var->val = ft_strdup(split[i]);
			start++;
		}
		i++;
	}
	free_tab(split);
}

static int	ft_check_read_opts(char **argv, t_env **env)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (argv[j][1] == '\0')
	{
		ft_putstr(ER_OPT);
		return (1);
	}
	else if (argv[j][1] == 'p')
		return (ft_p_read_opt(argv, env));
	else if (argv[j][1] == 'd')
		return (ft_d_read_opt(argv, env));
	else if (argv[j][1] == 's' && argv[j][2] == 0)
		return (ft_s_read_opt(argv, env));
	else if (argv[j][1] == 'n')
		return (ft_n_read_opt(argv, env, 0));
	else
	{
		ft_putstr(ER_OPT);
		return (1);
	}
	return (0);
}

int			ft_read(char **argv, t_env **env)
{
	char	*line;

	line = NULL;
	if (argv[1] == NULL)
		get_next_line(0, &line);
	else if (argv[1][0] == '-')
	{
		if (ft_check_read_opts(argv, env) == 1)
		{
			ft_strdel(&line);
			return (1);
		}
	}
	else
	{
		get_next_line(0, &line);
		if (line != NULL)
			ft_treat_read(argv, ft_strsplit(line, ' '), env, 1);
	}
	ft_strdel(&line);
	return (0);
}

int			ft_p_read_opt(char **argv, t_env **env)
{
	char	*line;
	int		i;

	line = NULL;
	i = 1;
	if (argv[i][2] != '\0')
		ft_putstr(argv[i++] + 2);
	else if (argv[++i] != NULL)
		ft_putstr(argv[i++]);
	else
	{
		ft_putstr(ER_ARG);
		return (1);
	}
	get_next_line(0, &line);
	if (argv[i] != NULL)
		ft_treat_read(argv, ft_strsplit(line, ' '), env, i);
	ft_strdel(&line);
	return (0);
}
