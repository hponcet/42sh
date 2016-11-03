/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsearch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 06:14:59 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/23 16:18:51 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_init_pn(int i)
{
	char	*prompt;

	ft_cursor_pos();
	prompt = ms_shell_name();
	if (i == 27)
		tputs(tgetstr("cr", 0), 1, ft_char);
	if (i == 4)
		tputs(tgetstr("do", 0), 1, ft_char);
	if (i == 0)
	{
		tputs(tgetstr("do", 0), 1, ft_char);
		return (1);
	}
	ft_putstr_fd(prompt, g_curs.fd);
	free(prompt);
	tputs(tgetstr("cd", 0), 1, ft_char);
	ft_cursor_pos();
	ft_init();
	return (1);
}

void		ft_hsearch(void)
{
	char	*buf;

	buf = ft_strnew(4);
	ft_printf("\x1B[1m\x1B[31m¿ \x1B[0m");
	ft_init();
	g_curs.sig = 0;
	while (42)
	{
		ft_signal();
		ft_bzero(buf, 4);
		read(0, buf, 4);
		if (g_curs.sig && ft_init())
			break ;
		if ((buf[0] == 27 || buf[0] == 4) && buf[1] == 0 && ft_init_pn(buf[0]))
			break ;
		if (ft_hsearch_key(buf))
			break ;
	}
	g_curs.sig = 0;
	ft_strdel(&buf);
}

void		ft_hsearch_enter(void)
{
	t_hist	*tmp;
	char	*find;

	if (!g_curs.retval)
	{
		tputs(tgetstr("cr", 0), 1, ft_char);
		tputs(tgetstr("cd", 0), 1, ft_char);
		ft_put_name();
		return ;
	}
	find = ft_joinf("*%s*", g_curs.retval);
	tmp = g_curs.history;
	while (tmp && ft_glob_compare(find, tmp->cmd) == 0)
		tmp = tmp->prev;
	if (tmp)
	{
		ft_strdel(&g_curs.retval);
		ft_del_chain();
		g_curs.initpos[0] -= 2;
		tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1,
					g_curs.initpos[1] - 1), 1, ft_char);
		tputs(tgetstr("cd", 0), 1, ft_char);
		ft_chain_addstr(tmp->cmd);
	}
	ft_strdel(&find);
}

void		ft_hsearch_display(char *cmd)
{
	t_hist	*tmp;
	char	*find;

	if (!g_curs.retval)
	{
		tputs(tgetstr("cd", 0), 1, ft_char);
		return ;
	}
	find = ft_joinf("*%s*", cmd);
	tmp = g_curs.history;
	tputs(tgetstr("cd", 0), 1, ft_char);
	while (tmp && ft_glob_compare(find, tmp->cmd) == 0)
		tmp = tmp->prev;
	if (tmp)
	{
		ft_putendl_fd("", g_curs.fd);
		ft_putstr_fd(tmp->cmd, g_curs.fd);
		g_curs.initpos[1] -= ft_char_count_sf(ft_strlen(tmp->cmd));
		tputs(tgoto(tgetstr("cm", 0), g_curs.initpos[0] - 1,
					g_curs.initpos[1] - 1), 1, ft_char);
		if (g_curs.retval)
			ft_putstr_fd(g_curs.retval, g_curs.fd);
	}
	ft_strdel(&find);
}

int			ft_hsearch_key(char *buf)
{
	if (ft_isprint(buf[0]) && buf[0] != '	')
	{
		ft_chain_addchar(buf[0]);
		ft_init_pos();
		ft_count_chain();
	}
	else if (buf[0] == 127 && buf[1] == 0 && g_curs.chain)
		ft_key_bs();
	else if (buf[0] == 10 && buf[1] == 0)
	{
		ft_hsearch_enter();
		return (1);
	}
	ft_key_norm();
	ft_hsearch_display(g_curs.retval);
	return (0);
}
