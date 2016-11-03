/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 21:21:28 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/21 19:10:36 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H
# include "libft.h"

typedef struct			s_hash
{
	char				*name;
	char				*value;
	struct s_hash		*next;
}						t_hash;

/*
**	ft_hash.c
*/
t_hash					**ft_hash_addpath(t_hash **htbl, char *path,
						int nb_case);
int						ft_hash(char *name, int nb_case);
t_hash					**ft_hash_add(t_hash **htbl, char *name,
						char *value, int nb_case);
void					ft_hash_delhtbl(t_hash **htbl, int nb_case);
char					*ft_hash_search(t_hash **htbl, char *name, int nb_case);

/*
**	ft_hash_new.c
*/
t_hash					**ft_hash_newtbl(int nb_case);
t_hash					*ft_hash_newfile(char *name, char *value);

#endif
