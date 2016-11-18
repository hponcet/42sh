/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 02:31:17 by hponcet           #+#    #+#             */
/*   Updated: 2016/11/16 17:42:56 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*new_blankstr(int i)
{
	char	*str;
	int		j;

	j = 0;
	if (i < 5)
		i = 5;
	str = ft_strnew(i);
	while (j < i)
		str[j++] = ' ';
	return (str);
}

static char	*nb_to_str(int nb)
{
	char	*str;
	char	*nbstr;
	int		i;
	int		j;

	nbstr = ft_itoa(nb);
	str = new_blankstr(ft_strlen(nbstr));
	j = ft_strlen(nbstr) - 1;
	i = ft_strlen(str) - 1;
	while (j >= 0 && i >= 0)
		str[i--] = nbstr[j--];
	ft_strdel(&nbstr);
	return (str);
}

static char	*timestamp_to_str(unsigned int timestamp)
{
	time_t		t;
	char		date[10];
	char		hour[8];
	char		*ret;
	struct tm	*ts;

	t = (time_t)timestamp;
	ts = localtime(&t);
	strftime(date, sizeof(date), "%m/%d/%y ", ts);
	strftime(hour, sizeof(hour), "%R  ", ts);
	ret = ft_strjoin(date, hour);
	return (ret);
}

static void	ft_histproc(t_hist *hist)
{
	t_hist	*tmp;
	char	*time;
	char	*input;
	char	*nb;
	int		i;

	tmp = hist;
	i = 1;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp != hist->next)
	{
		nb = nb_to_str(i);
		ft_putstr(nb);
		ft_strdel(&nb);
		ft_putstr("  ");
		time = timestamp_to_str(tmp->timestamp);
		ft_putstr(time);
		ft_strdel(&time);
		input = input_to_char(tmp->input);
		ft_putendl(input);
		ft_strdel(&input);
		tmp = tmp->next;
		i++;
	}
}

int			ft_history(char **cmd, t_shell *shell)
{
	t_hist	*hist;
	int	 	index;

	if (!(shell->hist))
		return (1);
	if (cmd[1] && cmd[2])
	{
		ft_putendl("42sh: fc: too few arguments");
		return (1);
	}
	index = bltn_hist_checkopt(cmd[1]);
	hist = NULL;
	if (index == 1)
		hist = bltn_hist_searchindex(cmd[1], shell);
	if (index == 0)
		hist = bltn_hist_searchstr(cmd[1], shell);
	if (index == -1)
		hist = shell->hist->prev;
	if (!hist)
		return (1);
	ft_histproc(hist);
	return (0);
}
