/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh_check_opt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 22:09:19 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/19 00:27:07 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void		ft_sh_help(void)
{
	int		fd;
	char	*tmp;

	tmp = ft_strnew(512);
	if (!(fd = open("./doc/help.md", O_RDONLY)))
		ft_putendl("Help file not found.");
	ft_putstr("\x1B[1m");
	while (read(fd, tmp, 512))
	{
		ft_putstr(tmp);
		ft_bzero(tmp, 512);
	}
	ft_putstr("\x1B[0m");
	close(fd);
	ft_strdel(&tmp);
	exit(0);
}

static t_shopt	*ret_opt(void)
{
	t_shopt	*opt;

	opt = (t_shopt*)malloc(sizeof(t_shopt));
	opt->dbg = 0;
	opt->htbl = 1;
	opt->prptnm = 1;
	opt->prptdir = 1;
	opt->envpath = 0;
	return (opt);
}

void			ft_sh_check_opt(int ac, char **av)
{
	t_shopt	*opt;

	opt = ret_opt();
	ac = 1;
	while (av[ac])
	{
		if (ft_strcmp("--debug=yes", av[ac]) == 0)
			opt->dbg = 1;
		if (ft_strcmp("--hash-table=no", av[ac]) == 0)
			opt->htbl = 0;
		if (ft_strcmp("--prompt-name=no", av[ac]) == 0)
			opt->prptnm = 0;
		if (ft_strcmp("--prompt-dir=no", av[ac]) == 0)
			opt->prptdir = 0;
		if (ft_strcmp("--default-path=yes", av[ac]) == 0)
			opt->envpath = 1;
		if (ft_strcmp("--help", av[ac]) == 0)
			ft_sh_help();
		ac++;
	}
	g_curs.opt = opt;
}
