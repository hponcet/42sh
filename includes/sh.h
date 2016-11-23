/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:07:09 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/22 15:53:41 by MrRobot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <libft.h>
# include <error.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <term.h>
# include <time.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/stat.h>

// types de maillons de l'arbre binaire
# define CMD 1 // commande
# define SEM 2 // point-virgule
# define PIP 3 // pipe
# define AND 4 // &&
# define OR 5 // ||

// types de redirection
# define REDIR 1 // >
# define DREDIR 2 // >>
# define BREDIR 3 // <
# define HEREDOC 4 // <<

// taille des tables de hashage en nb de cases
# define HASHLEN 5000

// Globing
typedef struct		s_glob
{
	char			*name;
	char			*path;
	struct s_glob	*next;
}					t_glob;

// Table de hashage
typedef struct			s_hash
{
	char				*name;
	char				*value;
	struct s_hash		*next;
}						t_hash;

// completion
typedef struct			s_compl
{
	int					type;
	size_t				len;
	size_t				id;
	char				*name;
	struct s_compl		*next;
	struct s_compl		*prev;
}						t_compl;

// redirections
typedef struct			s_redir
{
	int					type;
	char				*s; //contenu a extraire de la commande (ex : ">test_file")
	struct s_redir		*next;
}						t_redir;

// environnement
typedef struct			s_env
{
	char				*var;
	char				*val;
	struct s_env		*next;
}						t_env;

// caracteres de la commande
typedef struct			s_input
{
	char				c;
	struct s_input		*prev;
	struct s_input		*next;
}						t_input;

// historique
typedef	struct			s_hist
{
	unsigned int		timestamp;
	struct s_input		*input;
	struct s_hist		*prev;
	struct s_hist		*next;
}						t_hist;

// arbre binaire de commande
typedef struct			s_btree
{
	int					type;
	char				*str; // null si type != CMD
	struct s_redir		*redir; // null si aucune redir
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

// structure generale
typedef struct			s_shell
{
	int					fd[4]; // stin, stdout, stderr, tty, tty fantome
	int					status; // valeur de retour du dernier processus fils
	size_t				col; // nb colonnes fenetre
	size_t				row; // nb lignes
	size_t				winsize; // lignes * colonnes
	size_t				input_len; // longueur de l'input
	size_t				p_len; // longueur du prompt
	t_env				*env_lst;
	t_hist				*hist;
	t_hash				**hash_bin; // table de hashage pour les paths binaires
	int					hist_end; // flag fin de l'historique (derniere commande)
	t_input				*input;
	t_input				*input_save; // sauvegarde commande incomplete (quotes, pipe...)
	t_input				*buffer; // copier/coller
	t_input				*curs_pos; // position du curseur dans l'input
	char				*input_buf; // si deplacement dans historique et input != null
	t_btree				*tree;
	struct termios		termios; // termcaps modifies
	struct termios		term_save; // sauvegarde termcaps
}						t_shell;

// fonction micka
size_t					ft_list_size_index(t_input *start, t_input *end);
void					ft_lst_del(t_shell *shell, t_input *strt, t_input *end);
void					ft_back_quote(t_shell *shell);
void					ft_launch_cmd(t_shell *shell, t_btree *tree);
void					ft_input_add(t_input **curs, char c);
t_input					*ft_new_link(char c);
/// ERREURS ///
int						ft_put_error(char *error, int action);


int						exec_error(int errnum, char *arg); // cmd not found, fork, dup
int						cmd_error(int errnum, char c, char *s); // parsing pipe/redir
int						cd_error(int errnum, char *arg);
int						env_error(int errnum, int flag);
void					env_var_error(int errnum, char *cmd, char *arg);
int						exit_error(int errnum, char *arg);

/// FREE ///
void					free_input_list(t_input **input, size_t *nb_elem); // free tout ou partie d'input, nb_elem optionnel
void					free_tmp_inputs(t_shell *shell, int reset_save); // free input, buffers, input_save (optionnel), replace l'historique sur la derniere commande
void					free_env_var(t_env *env_var);
void					free_env_lst(t_env **env_lst);
void					free_redirs(t_redir **redirs);
void					free_btree(t_btree *tree);

/// INIT ET SIGNAUX ///
void					init_shell(t_shell *shell);
void					init_term(t_shell *shell);
void					restore_term(t_shell *shell);
void					reload_term(t_shell *shell);
void					sig_handler(int signum);
void					sig_handler1(int signum);
void					sig_handler_heredoc(int signum);
void					set_sig_handler(void);
t_shell					*get_struct(t_shell *struc); // renvoie la structure t_shell (avec 0 en param)

/// OUTILS ///
int						putchar(int c); // petit putchar des familles, la baaaase !
int						strrchr_outside_quotes(char *s, char c, char quote); // cherche c dans s en dehors de quote (a partir de la fin)
int						strchr_redir(t_btree *link);
int						is_str_quoted(char *s); // check si s est entre quote
char					*strdup_remove_quotes(char *s); // "exemple" ==> exemple (free s)
char					*str_replace_var(char *s, int start); // jesuis$USER ==> jesuistonpere
char					**strsplit_args(char const *s); // split arguments
char					**str_subsplit_arg(char const *s); // split des quotes pour interpretation
int						lst_is_empty(t_input *lst);
size_t					lst_len(t_input *lst);
char					*lst_to_str(t_input *lst);
t_input					*lst_rchr(t_input *input, char c);
t_input					*get_last_elem(t_input *lst); // retourne le dernier caractere de l'input
int						is_builtin(char *cmd); // gros if de porc (desole micka)

/// ENVIRONNEMENT ///
void					store_environ(t_shell *shell, char **environ);
int						store_env_var(t_env **env_lst, char *var, char *val);
int						del_env_var(t_env **env_lst, char *var);
int						dup_env_lst(t_env *env_lst, t_env **env_lst_cpy);
t_env					*get_env_ptr(t_env *env_lst, char *var);
char					**env_lst_to_array(t_env *env_lst);

int						check_env_var(char *env_var, char *cmd);
char					*env_var_to_value(char *var);
int						set_new_pwd(t_env *env_lst);

/// PROMPT ///
char					*get_prompt(t_env *env_lst); // retourne le path pour le prompt
char					*get_special_prompt(char c); // retourne le prompt associe a c (quote, hook..)
void					print_prompt(t_shell *shell, int special_prompt); // affiche un prompt tout mignon

/// INPUT ///
void					read_input(t_shell *shell); // boucle de lecture
void					print_input(t_shell *shell, t_input *curs_pos, // affiche l'input a partir du maillon curs_pos
						size_t p_len);
int						parse_input(t_shell *shell, char *buf,
						size_t buf_len, size_t p_len); // parsing des touches par categorie
void					store_input(t_shell *shell, char c); // ajoute un caractere dans l'input
void					delete_input(t_input **lst, t_input *input,
						t_shell *shell, int back); // supprime un caractere, shell et back optionnels
void					clear_input(t_shell *shell); // replace le curseur en debut de commande et supprime l'input

/// TOUCHES EDITION LIGNE ///
int						parse_keys1(t_shell *shell, char *buf);
int						parse_keys2(t_shell *shell, char *buf);
int						parse_keys3(t_shell *shell, char *buf, size_t buf_len);

int						move_left(t_shell *shell);
int						move_left_word(t_shell *shell);
int						move_right(t_shell *shell);
int						move_right_word(t_shell *shell);
int						move_line_start(t_shell *shell);
int						move_line_end(t_shell *shell);
int						move_line_up(t_shell *shell);
int						move_line_down(t_shell *shell);
int						backspace(t_shell *shell);
int						del(t_shell *shell);
int						cut_eol(t_shell *shell);
int						cut_all(t_shell *shell);
int						copy_eol(t_shell *shell);
int						copy_all(t_shell *shell);
void					store_buffer(t_input **buf, char c);
int						paste_buffer(t_shell *shell);

int						history_prev(t_shell *shell);
int						history_next(t_shell *shell);
t_hist					*store_hist(t_shell *shell);


/// CURSEUR ///
void					replace_cursor(t_shell *shell, int print, int back); // mouvement du curseur (g/d/h/b)
size_t					get_cursor_x_pos(t_input *input,
						t_input *pos, size_t p_len); // renvoie le x du curseur (p_len = longueur du prompt)

/// TRAITEMENT COMMANDE ///
int						handle_input(t_shell *shell); // touche return
int						check_input(t_shell *shell);
int						check_btree(t_btree *link);
char					check_separators(t_input *cmd, int reverse); // parsing pipes + &&
char					valid_input(t_input *input, char c); // check des quotes, parentheses backslash...
char					**parse_cmd(t_btree *link); // split en char**, appel des fonctions d'interpretation
t_btree					*store_cmd(char *str); // creer l'arbre binaire
char					*interpret_cmd_arg(char *cmd_arg); // interpretation des sous-argument de la cmd
char					*remove_cmd_redir(char *cmd, t_redir *redir);
int						replace_backslash(char **s, int i);
int						replace_tilde(char **s, int i);
int						replace_exit_value(char **s, int i);
int						handle_btree(t_shell *shell, t_btree *tree); // parcours de l'arbre binaire pour execution
int						handle_cmd(t_shell *shell, t_btree *link,
						int already_forked); // appel du parsing, des redirs et execution cmd
pid_t					redir_fork(char **cmd, t_shell *shell);
pid_t					exec_fork(char **cmd, char **env_array, t_env *env_lst,
						t_shell *shell); // (gus: ajout de la var shell pour la table de hashage dans binary_cmd)
pid_t					pipe_fork_father(t_shell *shell,
						t_btree *link);
pid_t					pipe_fork_child(t_shell *shell, t_btree *link);
int						handle_redirs(t_shell *shell, t_btree *link,
						char **cmd); // traitement des redirections
int						exec_redir_cmd(t_shell *shell, char **cmd);
int						fill_heredoc(char *delimiter, int *fd);

/// BUILTINS ///
int						builtins_cmd(char **cmd, t_env *env_lst, t_shell *shell); // execution builtin
int						ft_exit(char **cmd, t_shell *shell);
int						ft_cd(char **cmd, t_env *env_lst);
int						ft_echo(char **cmd);
int						ft_env(char **cmd, t_env *env_lst, int i, t_shell *shell);
int						ft_setenv(char **cmd, t_env **env_lst, int flag);
int						ft_unsetenv(char **cmd, t_env **env_lst);

/// EXECUCTION BINAIRES ///
int						binary_cmd(char **cmd, char **env_array,
						t_env *env_lst, t_hash **htbl); // execution binaire (gus: ajout de htbl pour rechercher dans la table de hashage)
char					*get_bin_path(char *cmd, t_env *env_lst);
int						check_bin_path(char *bin_path, char *cmd);
int						exec_bin(char *bin_path, char **argv, char **env);

/// FILE DESCRIPTOR ET RETOUR CMD ///
int						dup_std_fd(int *fd);
void					close_and_reset_fd(int *fd);
void					set_status(int *status, char **cmd);

/*
** /////////////////// GUS /////////////////////////////
** ////////////// BUILTIN HISTORY /////////////
** builtins/bltn_history.c
** Affiche l'historique des commande.
*/
int						ft_history(char **cmd, t_shell *shell);
/*
** builtins/bltn_history_opt.c
** Recherche dans l'historique par commande ou
** par event.
*/
int						bltn_hist_checkopt(char *cmd);
t_hist					*bltn_hist_searchstr(char *cmd, t_shell *shell,
						int opt);
t_hist					*bltn_hist_searchindex(char *cmd, t_shell *shell);

/*
** builtins/bltn_hsearch.c
** Recherche dans l'historique avec une commande
** commencant par '!' et constituee d'un event ou
** d'un chiffre.
*/
void					bltn_hsearch(t_shell *shell);
int						bltn_hsearch_key(t_shell *shell, char *buf);
int						bltn_hsearch_addchar(t_shell *shell, char *buf);
int						bltn_hsearch_ret(t_shell *shell, int c);
void					bltn_hsearch_display(t_shell *shell, t_hist *hist, int c);
/*
** /////////////// FILE HISTORY ///////////////
** // hist_file.c
** Lis le fichier .42_history situe dans le path $HOME
** et remplis l'historique des commande au demarage
** du shell.
** Reecrit a chaque commande le fichier .42_history
*/
int						history_error(int errnum, char *arg);
int						hist_proc(t_hist *hist, char *histpath);
int						hist_to_file(t_shell *shell, t_hist *hist);
void					input_to_hist(t_shell *shell, t_input *input, char *ts);
void					file_to_hist(t_shell *shell);
char					*hist_get_histpath(t_shell *shell);
/*
** // hist_check.c
** Check les doublons dans l'historique de commandes
*/
int						hist_checkdouble(t_shell *shell);

/* /////////////// INPUT TOOLS ///////////////
** // input_tools.c
** Plusieurs commandes pour l'adaptaion du 42sh.
*/
char					*input_to_char(t_input *input);
t_input					*char_to_input(char *str);
size_t					input_len(t_input *input);
void					free_input_from(t_shell *shell, t_input *input);

/* ////////////// COMPLETION ////////////////
** // compl_display.c
** Affichage de la completion.
** Contient une boucle while(42) qui attend certaine key
** pour la completion.
*/
int						compl_initprompt(t_shell *shell, int i);
int						compl_countfile(t_compl *print);
void					compl_display(t_shell *shell, t_compl *print,
						char *find);
/* // compl_key.c
** Adaptation de certaines touche speciales dans la
** boucle de completion :
** - fleche directionnelles droite et gauche
** - chaque lettres ascii
** - touche tabulation (pour faire defiler)
** - delete
** - touche esc/ctrl-d
*/
int						compl_key_dir(char *buf, t_compl **print, t_shell *shell,
						int pos);
int						compl_key(char *buf, t_compl **print, t_shell *shell,
						int pos);
/*
** // compl_str.c
** Gere l'affichage des differentes strings lors du
** defilement avec la touche tab.
*/
void					compl_addstrend(t_shell *shell, char *str, int type);
void					compl_addstr(t_shell *shell, char *str);
int						compl_retstr(t_compl *tmp, t_shell *shell, int pos, int i);
int						compl_retstrchar(t_compl *tmp, t_shell *shell, int pos,
						char c);
/*
** // compl_getinfo.c
** Fait une liste chainee avec les informations relative au
** path courant de la completion.
*/
char					*compl_name_wesp(char *str);
char					*compl_path_noesp(char *str);
t_compl					*compl_makefile(struct dirent *s_dir, char *path);
t_compl					*compl_makechain(char *path, t_compl *ret, char *find);
void					compl_sortchain(t_compl **list, t_compl *file);
char					*compl_getfind(char *str);

/*
** // compl.c
** compl : Fonction a appeler pour la completion qui determine
** si un binaire ou un path doit etre cherche.
** compl_delchain : free la lc du path courant ou du binaire.
*/
int						compl_wis(char *str);
void					compl_delchain(t_compl *chain);
void					compl_file(t_shell *shell, char *str);
void					compl_bin(t_shell *shell, char *str);
void					compl(t_shell *shell);

/*
** // compl_getpath.c
** Fonctions de gestion des paths. (ex: ~/42sh, /tmp,
** 42sh, ./ls, /bin/ls)
*/
void					compl_getpath(t_shell *shell, char **ret);
char					**compl_pathbin(t_shell *shell);

/*
** //////////////////// TABLE DE HASHAGE ///////////////
** hash.c
** Fonction de hashage simple qui aditionne les char en
** ascii puis les divise par un modulo de la taille de
** la table de hashage.
** ex:
** nmax(taille max du tableau) = 10
** tab[int nmax][t_hash*]
** "yo" = (121 + 111) % nmax = 232 % 10 = 2
** tab[2]->val = "yo"
*/
// Fonction pour ajouter un path entier a une table de hash
t_hash					**hash_addpath(t_hash **htbl, char *path, int nb_case);
// L'algoritme de hashage se trouve dans hash().
int						hash(char *name, int nb_case);
// Ajoute une valeur unique a la table de hash
t_hash					**hash_add(t_hash **htbl, char *name,
						char *value, int nb_case);
// Fonction pour supprimer la table de hashage
void					hash_delhtbl(t_hash **htbl, int nb_case);
// Rechercher dans la table de hashage
char					*hash_search(t_hash **htbl, char *name, int nb_case);

/*
** hash_new.c
** Malloc des maillons et de la table de hashage.
*/
t_hash					**hash_newtbl(int nb_case);
t_hash					*hash_newfile(char *name, char *value);

/*
** hash_bin.c
** Converti les paths des binaires vers
** (t_hash**)shell->hash_bin
*/
t_hash					**hash_bin(t_shell *shell);

/*
** ft_glob.c
*/
void				ft_glob(char **str);
char				*ft_glob_replace(char *cmd);
t_glob				*ft_glob_makefile(struct dirent *s_dir, char *path);
char				*ft_glob_tglobtostr(t_glob *lst);
void				ft_glob_sortchain(t_glob **ret, t_glob *file);
char				*ft_glob_makestr(char *path, char *find, char *absolute);
int					ft_glob_compare(char *s1, char *s2);
int					ft_glob_check(char *str);
void				ft_glob_path(char **ret);
void				ft_glob_delchain(t_glob *chain);

//////////////////////////////////////////////////////

#endif
