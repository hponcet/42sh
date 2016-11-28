/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:53:40 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/28 10:16:13 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_p_read_option(char **argv, t_env **env)
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

int		ft_d_read_option(char **argv, t_env **env)
{
	char	buf[7];
	char	*line;
	char	*tmp;
	char	limit;
	int		i;

	i = 1;
	line = NULL;
	ft_bzero(buf, 7);
	if (argv[i][2] != '\0')
		limit = argv[i++][2];
	else if (argv[++i] != NULL)
		limit = argv[i++][0];
	else
	{
		ft_putstr(ER_ARG);
		return (1);
	}
	while (read(0, buf, 6) > 0)
	{
		if (buf[0] == limit)
			break ;
		else
		{
			if (line == NULL)
				line = ft_strdup(&buf[0]);
			else
			{
				tmp = ft_strjoin(line, &buf[0]);
				free(line);
				line = tmp;
			}
			ft_putchar(buf[0]);
		}
		ft_bzero(buf, 7);
	}
	if (line != NULL)
	{
		if (argv[i] != NULL)
			ft_treat_read(argv, ft_strtab(line), env, i);
		ft_strdel(&line);
	}
	return (0);
}
