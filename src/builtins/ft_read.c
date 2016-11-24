/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:44:55 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/24 20:54:26 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_read_whitout_options(char **argv, char *line, t_env **env)
{
	char	**split;
	char	*tmp;
	t_env	*var;
	int		i;
	int		j;

	i = 0;
	j = 1;
	split = ft_strsplit(line, ' ');
	while (split[i] != NULL)
	{
		if (argv[j] != NULL && (var = get_env_ptr(*env, argv[j])) != NULL)
		{
			free(var->val);
			var->val = ft_strdup(split[i]);
			j++;
		}
		else if (argv[j] == NULL)
		{
			tmp = ft_strjoin(var->val, split[i]);
			free(var->val);
			var->val = tmp;
		}
		i++;
	}
	free_tab(split);
	return (1);
}

int			ft_read(char **argv, t_env **env)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) != -1)
	{
		if (argv[1] == NULL)
			return (1);
		else if (argv[1][0] != '-')
			return (ft_read_whitout_options(argv, line, env));
		ft_strdel(&line);
	}
	return (1);
}
