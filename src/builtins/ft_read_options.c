/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MrRobot <mimazouz@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:53:40 by MrRobot           #+#    #+#             */
/*   Updated: 2016/11/28 12:11:04 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

static char	*ft_treat_d_opt(char limit)
{
	char	*line;
	char	*tmp;
	char	buf[7];

	line = NULL;
	ft_bzero(buf, 7);
	while (read(0, buf, 6) > 0)
	{
		if (buf[0] == limit)
			break ;
		else
		{
			if (line == NULL)
				line = ft_strdup(&buf[0]);
			else if (ft_isprint(buf[0]) == 1 || buf[0] == '\n')
			{
				tmp = ft_strjoin(line, &buf[0]);
				free(line);
				line = tmp;
			}
			ft_putchar(buf[0]);
		}
		ft_bzero(buf, 7);
	}
	return (line);
}

int			ft_d_read_opt(char **argv, t_env **env)
{
	t_shell	*shell;
	char	*line;
	char	limit;
	int		i;

	i = 1;
	if (argv[i][2] != '\0')
		limit = argv[i++][2];
	else if (argv[++i] != NULL)
		limit = argv[i++][0];
	else
	{
		ft_putstr(ER_ARG);
		return (1);
	}
	shell = get_struct(0);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->termios);
	if ((line = ft_treat_d_opt(limit)) != NULL)
	{
		if (argv[i] != NULL)
			ft_treat_read(argv, ft_strtab(line), env, i);
		ft_strdel(&line);
	}
	restore_term(shell);
	return (0);
}
