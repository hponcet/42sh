/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:04:35 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/20 21:42:53 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		main(int ac, char **av, char **env)
{
	g_curs.env = ft_change_shlvl(ms_get_env(env));
	ft_load(ac, av);
	ft_display();
}
