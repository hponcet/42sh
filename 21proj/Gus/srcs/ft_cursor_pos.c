/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 18:07:36 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/04 13:43:25 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				write_data(const char *data, const size_t len)
{
	const char	*cp_data;
	ssize_t		n;

	cp_data = data;
	n = write(g_curs.fd, cp_data, len);
	if (n < 0)
		return (-1);
	return (0);
}

static unsigned char	*read_data(void)
{
	unsigned char	*buffer;
	int				n;

	buffer = (unsigned char*)malloc(sizeof(unsigned char) * 128);
	ft_bzero(buffer, 128);
	while (42)
	{
		n = read(g_curs.fd, buffer, 128);
		if (n > 0)
			return (buffer);
		else if (n == 0)
		{
			free(buffer);
			return (NULL);
		}
	}
	return (buffer);
}

static int				ft_term_cread(int i)
{
	if (i == 0)
	{
		if (tcsetattr(g_curs.fd, TCSANOW, &g_curs.term.curs_pos) == -1)
			return (-1);
	}
	else
	{
		if (tcsetattr(g_curs.fd, TCSANOW, &(g_curs.term.mod)) == -1)
			return (-1);
	}
	return (0);
}

static int				ft_curs_pos_parse(unsigned char *result)
{
	int		i;

	i = -1;
	if (!result)
		return (0);
	if (result[++i] != 27)
		return (0);
	if (result[++i] != '[')
		return (0);
	g_curs.curs_pos[1] = 0;
	while (result[++i] >= '0' && result[i] <= '9')
		g_curs.curs_pos[1] = 10 * g_curs.curs_pos[1] + result[i] - '0';
	if (result[i] != ';')
		return (0);
	g_curs.curs_pos[0] = 0;
	while (result[++i] >= '0' && result[i] <= '9')
		g_curs.curs_pos[0] = 10 * g_curs.curs_pos[0] + result[i] - '0';
	return (1);
}

void					ft_cursor_pos(void)
{
	unsigned char		*result;

	if (ft_term_cread(0) == -1)
		return ;
	if (write_data("\033[6n", 4) == -1)
		return ;
	result = read_data();
	if (ft_curs_pos_parse(result) == 0)
	{
		free(result);
		ft_cursor_pos();
	}
	else
	{
		ft_term_cread(1);
		free(result);
	}
}
