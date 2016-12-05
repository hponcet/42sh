/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:12:09 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/29 21:23:20 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	put_export_vars(t_env *env_lst)
{
	while (env_lst)
	{
		ft_putstr("declare -x ");
		ft_putstr(env_lst->var);
		if (env_lst->val)
		{
			ft_putstr("=\"");
			if (env_lst->val[0])
				ft_putstr(env_lst->val);
			ft_putstr("\"\n");
		}
		else
			ft_putchar('\n');
		env_lst = env_lst->next;
	}
}

static void	store_export_var(t_env **env_lst, char *var, char *val)
{
	t_env	*new;
	t_env	*last;

	if ((new = get_env_ptr(*env_lst, var)))
	{
		free(var);
		if (val)
		{
			free(new->val);
			new->val = val;
		}
	}
	else
	{
		if (!(new = (t_env*)malloc(sizeof(t_env))))
			ft_put_error(ER_MEM, 1);
		new->var = var;
		new->val = val;
		new->next = NULL;
		if (!(*env_lst))
			*env_lst = new;
		else if ((last = get_last_env_elem(*env_lst)))
			last->next = new;
	}
	new->local = 0;
}

static void	parse_export_var(t_env *env_lst, char *arg)
{
	int		i;
	char	*var;
	char	*val;

	if ((i = ft_strchr_index(arg, '=')) == -1)
	{
		var = ft_strdup(arg);
		val = NULL;
	}
	else
	{
		var = ft_strsub(arg, 0, i);
		if (i == ((int)ft_strlen(arg) - 1))
			val = ft_strdup("");
		else
			val = ft_strsub(arg, i + 1, (ft_strlen(arg) - i - 1));
	}
	store_export_var(&env_lst, var, val);
}

int			ft_export(char **cmd, t_env *env_lst)
{
	int	i;
	int	print;

	i = 1;
	print = 0;
	if (!cmd[i])
	   put_export_vars(env_lst);
	else if (!ft_strcmp(cmd[i], "-p") && ++print)
		i++;
	else if (cmd[i][0] == '-')
		return (export_error(0, cmd[i]));
	while (cmd[i])
	{
		if (check_env_var(cmd[i], "export") == -1)
		{
			export_error(1, NULL);
			return (1);
		}
		parse_export_var(env_lst, cmd[i++]);
	}
	if (print)
		put_export_vars(env_lst);
	return (0);
}
