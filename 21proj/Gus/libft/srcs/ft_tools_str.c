/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 05:31:31 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/16 21:43:25 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_str_tools_len_char(int i)
{
	char		*buf;
	int			j;

	buf = NULL;
	j = 0;
	buf = (char*)malloc(sizeof(char) * i + 2);
	if (!buf)
		return (NULL);
	buf[i] = '\0';
	while (j < i)
	{
		buf[j] = ' ';
		j++;
	}
	return (buf);
}

char		*ft_str_tools_wflags_char(char *buf, char *str, t_print *list)
{
	int		b;
	int		s;

	if (ft_strlen(buf) < ft_strlen(str) && list->len > 0 && list->conv !=
			's' && list->conv != 'S')
		return (str);
	if (list->prec < (int)ft_strlen(str) && list->prec > -1 && list->conv !=
			'S' && list->conv == 's')
		s = list->prec - 1;
	else
		s = ft_strlen(str) - 1;
	b = ft_strlen(buf) - 1;
	while (s >= 0 && b >= 0)
	{
		buf[b] = str[s];
		b--;
		s--;
		if (s > 0 && (list->conv == 'd' || list->conv == 'D' ||
					list->conv == 'i') && (str[s] == '-' ||
					str[s] == '+' || str[s] == ' ') && (list->flags[3] ==
					'0') && buf[b] == '0')
			s--;
	}
	return (buf);
}

char		*ft_str_tools_mflags_char(char *buf, char *str, t_print *list)
{
	int		s;
	int		i;

	i = 0;
	if (list->prec >= 0 && list->prec < (int)ft_strlen(str) && list->conv
			!= 'x' && list->conv != 'X' && list->conv != 'o' && list->conv
			!= 'O' && list->conv != '%' && list->conv != 'd' && list->conv
			!= 'D' && list->conv != 'i' && list->conv != 'u' && list->conv
			!= 'U')
		s = list->prec;
	else
		s = ft_strlen(str);
	while (i < s)
	{
		buf[i] = str[i];
		i++;
	}
	return (buf);
}

void		ft_arg_s_ret_null(void)
{
	char	*buf;

	buf = ft_strdup("(null)");
	ft_str_buf_to_bufret(buf);
	free(buf);
}
