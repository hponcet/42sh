/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 05:04:19 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 17:18:23 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_put_name(void)
{
	char	*prompt;

	ft_cursor_pos();
	if (g_curs.curs_pos[0] > 1)
		ft_putstr(__BPERC__);
	prompt = ms_shell_name();
	ft_putstr_fd(prompt, g_curs.fd);
	free(prompt);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
	ft_cursor_pos();
}

void	ft_init_prompt(void)
{
	ft_heredoc_del();
	g_curs.qt = 0;
	ft_strdel(&g_curs.tmpchain);
	g_curs.hist = 0;
	if (g_curs.curs_pos[0] > 1)
		ft_printf(__BWHT"%"__CLR_END__);
	ft_putendl("");
	ft_put_name();
	ft_del_chain();
	ft_strdel(&g_curs.retval);
	ft_init();
}

char	*ms_shell_name(void)
{
	char	*name;
	char	*dir;
	char	*tmp;

	if (g_curs.opt->prptnm)
		name = ft_strdup(__PROMPT_NAME__);
	else
		name = ft_strdup("");
	if (g_curs.opt->prptdir)
	{
		dir = ms_shell_name_getdir();
		tmp = ft_strjoin(__DIR_COLOR__, dir);
		free(dir);
		dir = ft_strjoin(tmp, __DIR_COLOR_END__);
		free(tmp);
	}
	else
		dir = ft_strdup("");
	tmp = ft_strjoin(name, dir);
	if (tmp[0] == '\0')
		tmp = ft_strdup("21sh $> ");
	free(name);
	free(dir);
	return (tmp);
}

char	*ms_shell_name_getdir(void)
{
	char	*tmp;
	char	*dir;
	int		i;
	int		j;

	i = 0;
	tmp = NULL;
	tmp = getcwd(tmp, MAXPATHLEN);
	if (tmp)
	{
		j = ft_strlen(tmp);
		while (tmp[--j] != '/')
			i++;
		if (!(dir = (char*)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		dir[i] = '\0';
		i = -1;
		while (tmp[++j])
			dir[++i] = tmp[j];
	}
	if (i == 0 || i == -1)
		dir = ft_strdup("/");
	free(tmp);
	return (dir);
}
