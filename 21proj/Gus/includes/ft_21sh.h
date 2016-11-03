/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hponcet <hponcet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 20:03:31 by hponcet           #+#    #+#             */
/*   Updated: 2016/10/25 16:56:31 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_hash.h"
# include "../libft/includes/ft_colors.h"
# include "ms_minishell.h"
# include "ft_config.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <dirent.h>
# include <sys/stat.h>

typedef struct		s_glob
{
	char			*name;
	char			*path;
	struct s_glob	*next;
}					t_glob;

typedef struct		s_shopt
{
	int				dbg;
	int				htbl;
	int				prptdir;
	int				prptnm;
	int				envpath;
}					t_shopt;

typedef struct		s_compl
{
	int				type;
	size_t			len;
	size_t			id;
	char			*name;
	struct s_compl	*next;
	struct s_compl	*prev;
}					t_compl;

typedef struct		s_hd
{
	char			*init_cmd;
	char			*cmd;
	char			*trigger;
}					t_hd;

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_term
{
	struct termios	mod;
	struct termios	init;
	struct termios	curs_pos;
}					t_term;

typedef struct		s_chain
{
	char			c;
	size_t			word;
	size_t			sel;
	int				*cp;
	size_t			id;
	struct s_chain	*next;
	struct s_chain	*prev;
}					t_chain;

typedef struct		s_curs
{
	int				*curs_pos;
	int				*ws;
	int				hist;
	int				qt;
	size_t			nb_chr;
	size_t			id;
	struct s_chain	*select;
	struct s_chain	*ls;
	struct s_chain	*next;
	struct s_chain	*prev;
	t_hd			*hd;
	int				fd;
	t_shopt			*opt;
	t_hash			**hash_bin;
	t_hash			**alias;
	char			**env;
	int				*initpos;
	t_term			term;
	t_chain			*chain;
	char			*tmpchain;
	char			*copy;
	t_hist			*history;
	char			*retval;
	int				error;
	int				sig;
}					t_curs;

t_curs				g_curs;

/*
** ft_alias.c
*/
char				*ft_alias_delquotes(char *str);
void				ft_alias_htbltofile(void);
void				ft_alias_htbladd(char *buf);
void				ft_alias_gethtbl(void);
int					ft_alias(char *cmd);
int					ft_alias_unalias(char *cmd);
int					ft_alias_search(char **cmd);
int					ft_alias_new(char **cmd);

/*
** ft_hsearch.c
*/
void				ft_hsearch(void);
int					ft_hsearch_key(char *buf);
void				ft_hsearch_display(char *cmd);
int					ft_init_pn(int i);

/*
** ft_hash_bin.c
*/
void				ft_sh_check_opt(int ac, char **av);

/*
** ft_hash_bin.c
*/
t_hash				**ft_hash_bin(void);

/*
** ft_glob.c
*/
char				*ft_glob(char *cmd);
char				*ft_glob_replace(char *cmd);
t_glob				*ft_glob_makefile(struct dirent *s_dir, char *path);
char				*ft_glob_tglobtostr(t_glob *lst);
void				ft_glob_sortchain(t_glob **ret, t_glob *file);
char				*ft_glob_makestr(char *path, char *find, char *absolute);
int					ft_glob_compare(char *s1, char *s2);
int					ft_glob_check(char *str);
void				ft_glob_path(char **ret);
void				ft_glob_delchain(t_glob *chain);

/*
** ft_compl.c
*/
char				*ft_compl(char *str);
void				ft_compl_bin(char *str);
void				ft_compl_file(char *str);
void				ft_compl_delchain(t_compl *chain);
int					ft_compl_wis(char *str);
int					ft_compl_key(char *buf, t_compl **print, char *find,
					int *pos);
int					ft_compl_countfile(t_compl *print);
void				ft_compl_display(t_compl *print, char *find);
void				ft_compl_getpath(char **ret);
t_compl				*ft_compl_makefile(struct dirent *s_dir, char *path);
t_compl				*ft_compl_makechain(char *path, t_compl *ret, char *find);
void				ft_compl_sortchain(t_compl **list, t_compl *file);
char				*ft_compl_getfind(char *str);
int					ft_compl_key_dir(char *buf, t_compl **print,
					char *find, int *pos);
void				ft_compl_addstrend(char *str, int type);
void				ft_compl_addstr(char *str);
int					ft_compl_retstr(t_compl *tmp, char *find, int *pos, int i);
int					ft_compl_retstrchar(t_compl *tmp, char *find, int *pos,
					char c);

/*
** ft_dollar.c
*/
char				*ft_get_env_value(char *cmd);
char				*ft_get_var_value(char *str);
char				*ft_replace_cmd_var(char *cmd, char *var, char *value);
char				*ft_dollar(char *str);

/*
** ft_cindex.c
*/
int					ft_cindex_count_quote(char *s, int i, char c);
int					ft_cindex_count_quote_rev(char *s, int i, char c);
int					ft_cindex_noquote(char *str, char c);
int					ft_cindexfrom_noquote_rev(char *str, int index, char c);
int					ft_cindex_noquote_rev(char *str, char c);

/*
** ft_redir_heredoc.c
*/
int					ft_heredoc_check(void);
int					ft_heredoc_new(void);
void				ft_heredoc_del(void);
void				ft_heredoc_proc(void);
int					ft_heredoc_exec(char *str);
int					ft_heredoc_addcontent(char *str);
int					ft_heredoc_endtrig(char *str);
char				*ft_heredoc_initcmd(char *str);
char				*ft_heredoc_cmd(char *str);
void				ft_heredoc_err(int i);

/*
** ft_strsub_quote.c
*/
char				*ft_join_tab(char **tb);

/*
** ft_getfd.c.c
*/
void				get_fd(void);

/*
** ft_cmd_v.c
*/
void				ft_cmd_v(char *buf);

/*
** ft_redir_fd.c
*/
void				ft_redir_fd(char **cmd);

/*
** ft_redir_fd_right.c
*/
void				ft_redir_fd_right(char **cmd);

/*
** ft_cindex_noquote.c
*/
int					ft_cindex_noquote(char *str, char c);
int					ft_cindex_noquote_rev(char *str, char c);
int					ft_cindexfrom_noquote_rev(char *str, int index, char c);
int					ft_cmd_count_quote_rev(char *s, int i, char c);

/*
** ft_redir_tools.c
*/
int					ft_redir_isgoodchar(char i);
char				*ft_redir_getfilename(char *cmd, char c);

/*
** ft_redir.c
*/
void				ft_redir(char **cmd);
void				ft_redir_exec(char *cmd);
void				ft_redir_left(char **cmd);

/*
** ft_redir_right.c
*/
void				ft_redir_right(char **cmd);

/*
** ft_redir_right.c
*/
void				ft_redir_double_right(char **cmd);

/*
** ft_ast.c
*/
void				ft_ast(char *cmd);
void				ft_pipe(char *cmd1, char *cmd2);

/*
** ft_cursor_pos.c
*/
void				get_fd(void);
void				ft_cursor_pos(void);
int					ft_term_init(void);
int					ft_term_reset(void);

/*
** ft_sh_name.c
*/
char				*ms_shell_name(void);
char				*ms_shell_name_getdir(void);
void				ft_put_name(void);

/*
** ft_signal.c
*/
void				ft_signal(void);
void				ft_catch_signal(int signo);
void				ft_signal_onexec(void);
void				ft_init_prompt(void);

/*
** ft_window_size.c
*/
void				ft_window_size(void);

/*
** ft_history.c
*/
void				ft_history(char *cmd);

/*
** ft_display.c
*/
void				ft_display(void);

/*
** ft_init.c
*/
char				**ft_change_shlvl(char **env);
void				ft_load(int ac, char**av);
int					ft_init(void);
void				ft_init_window(void);

/*
** ft_history.c
*/
void				ft_init_hist(void);
void				ft_hist_addtohist(char *ncmd);
void				ft_histtochain(void);

/*
** ft_quote.c
*/
int					ft_quote(void);
int					*ft_quote_initteub(void);

/*
** ft_chain.c
*/
void				ft_chain_firstchar(int c);
void				ft_chain_midchar(int c);
void				ft_chain_lastchar(int c);
t_chain				*ft_new_chr(int c);

/*
** ft_chain.c
*/
void				ft_chain_addstr(char *str);
void				ft_chain_addchar(int c);

/*
** ft_chain_tools.c
*/
void				ft_init_pos(void);
int					ft_count_chain(void);
void				ft_find_word(void);
void				ft_make_retval(void);
void				ft_del_chain(void);

/*
** ft_char.c
*/
int					ft_char(int i);
int					ft_char_tc(t_chain *chr);
int					ft_str_tc(t_chain *chr);
int					ft_char_count_sf(int len);

/*
** ft_key.c
*/
void				ft_key(char *buf);
void				ft_key_norm(void);
void				ft_key_group_dir(char *buf);

/*
**	ft_key_ctrl_d.c
*/
void				ft_key_ctrl_d(void);

/*
** ft_key_directional.c
*/
void				ft_key_directional(const char *buf);
void				ft_key_left(void);
void				ft_key_right(void);

/*
** ft_key_up.c
*/
void				ft_key_up(void);

/*
** ft_key_down.c
*/
void				ft_key_down(void);

/*
** ft_key_shift_dir_right.c
*/
void				ft_shift_dir_right(void);
void				ft_reset_select(void);

/*
** ft_key_shift_dir_left.c
*/
void				ft_shift_dir_left(void);
/*
** ft_key_enter.c
*/
int					ft_key_enter(void);

/*
** ft_key_bs.c
*/
void				ft_key_bs(void);

/*
** ft_key_del.c
*/
void				ft_key_del(void);

/*
** ft_key_del.c
*/
void				ft_key_home(char *buf);
int					ft_printf(const char *format, ...);

/*
** ft_key_opt_directional.c
*/
void				ft_key_opt_directional(char *buf);

/*
** ft_key_opt_copy.c
*/
void				ft_func_copy(char *buf);
void				ft_copy(void);
void				ft_paste(void);
void				ft_cut(void);

/*
** ft_debug.c
*/
void				ft_debug(void);
void				ft_debug_head(void);

#endif

/*
**   me    Fin de tous les modes tels que so, us, mb, md et mr
**   us    Début de soulignement
**   md    Début de mode gras
**   mr    Début de mode inverse
**   sc	   save pos curs
**   rc    restor pos curs
**   cm	   cursor move
**   up	   ^
**   do	   v
**   nd	   >
**   le	   <
**   cb    Effacer depuis le début de la ligne jusqu'au curseur
**   dc    Effacer 1 caractères
**   ce	   Effacer jusqu'a la fin de la ligne
**   do    Descendre le curseur d'une ligne
**   ll	   Déplacer le curseur au coin inférieur gauche
*/
