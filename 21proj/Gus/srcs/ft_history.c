/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 02:46:43 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 17:48:24 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void		ft_hist_addtofile(char *homepath)
{
	int		fd;
	char	ret;
	t_hist	*tmp;

	ret = '\n';
	if (!homepath)
		return ;
	fd = open(homepath, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return ;
	if (!g_curs.history)
	{
		close(fd);
		return ;
	}
	while (g_curs.history)
	{
		write(fd, g_curs.history->cmd, ft_strlen(g_curs.history->cmd));
		write(fd, &ret, 1);
		tmp = g_curs.history;
		g_curs.history = g_curs.history->prev;
		free(tmp->cmd);
		free(tmp);
	}
	close(fd);
}

static void		ft_hist_makechain(char *homepath)
{
	int		fd;
	char	*buf;
	t_hist	*new;
	t_hist	*tmp;

	tmp = NULL;
	new = NULL;
	fd = open(homepath, O_RDONLY, 0644);
	if (fd == -1)
		return ;
	while (get_next_line(fd, &buf) > 0)
	{
		new = (t_hist*)malloc(sizeof(t_hist));
		new->next = tmp;
		if (tmp)
			tmp->prev = new;
		new->prev = NULL;
		new->cmd = ft_strdup(buf);
		if (!g_curs.history)
			g_curs.history = new;
		tmp = new;
		free(buf);
		buf = NULL;
	}
	close(fd);
}

void			ft_init_hist(void)
{
	char	*homepath;

	homepath = ft_strjoin(getenv("HOME"), "/.21history");
	if (g_curs.history)
		while (g_curs.history->next)
			g_curs.history = g_curs.history->next;
	if (!homepath)
		return ;
	ft_hist_addtofile(homepath);
	ft_hist_makechain(homepath);
	free(homepath);
}

void			ft_hist_addtohist(char *ncmd)
{
	t_hist	*tmp;
	int		i;

	i = 0;
	while (ncmd[i])
	{
		if (ncmd[i] == '\n')
			ncmd[i] = ' ';
		i++;
	}
	if (g_curs.history && ft_strcmp(ncmd, g_curs.history->cmd) == 0)
		return ;
	tmp = (t_hist*)malloc(sizeof(t_hist));
	tmp->prev = g_curs.history;
	tmp->next = NULL;
	tmp->cmd = ft_strdup(ncmd);
	if (g_curs.history)
		g_curs.history->next = tmp;
	g_curs.history = tmp;
}

void			ft_histtochain(void)
{
	int		i;

	i = 0;
	if (g_curs.chain)
		ft_del_chain();
	tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1,
				g_curs.initpos[1] - 1), 1, ft_char);
	tputs(tgoto(tgetstr("cd", 0), 1, 0), 1, ft_char);
	g_curs.id = 1;
	g_curs.prev = NULL;
	g_curs.next = NULL;
	free(g_curs.retval);
	g_curs.retval = NULL;
	ft_cursor_pos();
	g_curs.initpos[0] = g_curs.curs_pos[0];
	g_curs.initpos[1] = g_curs.curs_pos[1];
	while (g_curs.history->cmd[i])
	{
		ft_chain_addchar(g_curs.history->cmd[i]);
		ft_count_chain();
		i++;
	}
	g_curs.hist = 0;
	ft_init_hist();
}
