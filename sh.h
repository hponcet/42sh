/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 17:07:09 by fkoehler          #+#    #+#             */
/*   Updated: 2016/11/12 16:43:00 by hponcet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <libft.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <term.h>
# include <fcntl.h>
# include <sys/ioctl.h>

// types de maillons de l'arbre binaire
# define CMD 1 // commande
# define SEM 2 // point-virgule
# define PIP 3 // pipe

// types de redirection
# define REDIR 1 // >
# define DREDIR 2 // >>
# define BREDIR 3 // <
# define HEREDOC 4 // <<

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
	int					fd[4]; // stin, stdout, stderr, tty
	size_t				col; // nb colonnes fenetre
	size_t				row; // nb lignes
	size_t				winsize; // lignes * colonnes
	size_t				input_len; // longueur de l'input
	size_t				p_len; // longueur du prompt
	t_env				*env_lst;
	t_hist				*hist;
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

void					quit_error(int errnum); // termcaps, malloc.. + exit()
int						exec_error(int errnum, char *arg); // cmd not found, fork, dup
int						common_error(int errnum, char *value);
int						cmd_error(int errnum, char c, char *s); // parsing pipe/redir
int						cd_error(int errnum, char *arg);
int						env_error(int errnum, int flag);
void					env_var_error(int errnum, char *cmd, char *arg);
int						exit_error(int errnum, char *arg);

void					free_input_list(t_input **input, size_t *nb_elem); // free tout ou partie d'input, nb_elem optionnel
void					free_tmp_inputs(t_shell *shell, int reset_save); // free input, buffers, input_save (optionnel), replace l'historique sur la derniere commande
void					free_env_var(t_env *env_var);
void					free_env_lst(t_env **env_lst);
void					free_redirs(t_redir **redirs);
void					free_btree(t_btree *tree);

void					init_shell(t_shell *shell);
void					init_term(t_shell *shell);
void					restore_term(t_shell *shell);
void					reload_term(t_shell *shell);
void					sig_handler(int signum);
void					sig_handler1(int signum);
void					sig_handler_heredoc(int signum);
void					set_sig_handler(void);
t_shell					*get_struct(t_shell *struc); // renvoie la structure t_shell (avec 0 en param)

int						putchar(int c); // petit putchar des familles, la baaaase !
int						strrchr_outside_quotes(char *s, char c, char quote); // cherche c dans s en dehors de quote (a partir de la fin)
int						strchr_redir(t_btree *link);
int						is_str_quoted(char *s); // check si s est entre quote
char					*strdup_remove_quotes(char *s); // "exemple" ==> exemple (free s)
char					*str_replace_var(char *s, int start); // jesuis$USER ==> jesuistonpere
char					**strsplit_args(char const *s); // split arguments
char					**str_subsplit_arg(char const *s); // split des quotes pour interpretation
size_t					lst_len(t_input *lst);
char					*lst_to_str(t_input *lst);
t_input					*lst_rchr(t_input *input, char c);
t_input					*get_last_elem(t_input *lst); // retourne le dernier caractere de l'input
int						is_builtin(char *cmd); // gros if de porc (desole micka)

void					store_environ(t_shell *shell, char **environ);
int						store_env_var(t_env **env_lst, char *var, char *val);
int						del_env_var(t_env **env_lst, char *var);
int						dup_env_lst(t_env *env_lst, t_env **env_lst_cpy);
t_env					*get_env_ptr(t_env *env_lst, char *var);
char					**env_lst_to_array(t_env *env_lst);

int						check_env_var(char *env_var, char *cmd);
char					*env_var_to_value(char *var);
int						set_new_pwd(t_env *env_lst);

char					*get_prompt(t_env *env_lst); // retourne le path pour le prompt
char					*get_special_prompt(char c); // retourne le prompt associe a c (quote, hook..)
void					print_prompt(t_shell *shell, int special_prompt); // affiche un prompt tout mignon

void					read_input(t_shell *shell); // boucle de lecture
void					print_input(t_shell *shell, t_input *curs_pos, // affiche l'input a partir du maillon curs_pos
						size_t p_len);
int						parse_input(t_shell *shell, char *buf,
						size_t buf_len, size_t p_len); // parsing des touches par categorie
void					store_input(t_shell *shell, char c); // ajoute un caractere dans l'input
void					delete_input(t_input **lst, t_input *input,
						t_shell *shell, int back); // supprime un caractere, shell et back optionnels
void					clear_input(t_shell *shell); // replace le curseur en debut de commande et supprime l'input

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
int						hist_proc(t_hist *hist, char *histpath);
int						hist_to_file(t_shell *shell, t_hist *hist);
void					input_to_hist(t_shell *shell, t_input *input);
void					file_to_hist(t_shell *shell);
char					*hist_get_histpath(t_shell *shell);

/////////// input_tools.c ///////////// (pour Gus)
char					*input_to_char(t_input *input);
t_input					*char_to_input(char *str);
size_t					input_len(t_input *input);

void					replace_cursor(t_shell *shell, int print, int back); // mouvement du curseur (g/d/h/b)
size_t					get_cursor_x_pos(t_input *input,
						t_input *pos, size_t p_len); // renvoie le x du curseur (p_len = longueur du prompt)

int						handle_input(t_shell *shell); // touche return : 1ers cas d'erreurs + appel des fonctions de traitement de la cmd
int						check_pipes(t_input *cmd, int reverse);
char					valid_input(t_input *input, char c); // check des quotes, parentheses backslash...
char					**parse_cmd(t_btree *cmd); // split en char**, appel des fonctions d'interpretation
t_btree					*store_cmd(char *str); // creer l'arbre binaire
char					*interpret_cmd_arg(char *cmd_arg); // interpretation des sous-argument de la cmd
char					*remove_cmd_redir(char *cmd, t_redir *redir);
int						replace_backslash(char **s, int i);
int						replace_tilde(char **s, int i);
int						handle_btree(t_shell *shell, t_btree *tree); // parcours de l'arbre binaire pour execution
int						handle_cmd(t_shell *shell, t_btree *link,
						int already_forked); // appel du parsing, des redirs et execution cmd
pid_t					redir_fork(char **cmd, t_shell *shell);
pid_t					exec_fork(char **cmd, char **env_array, t_env *env_lst);
pid_t					pipe_fork_father(t_shell *shell,
						t_btree *link);
pid_t					pipe_fork_child(t_shell *shell, t_btree *link);
int						handle_redirs(t_shell *shell, t_btree *link,
						char **cmd); // traitement des redirections
int						exec_redir_cmd(t_shell *shell, char **cmd);
int						fill_heredoc(char *delimiter, int *fd);

int						builtins_cmd(char **cmd, t_env *env_lst); // execution builtin
int						ft_exit(char **cmd);
int						ft_cd(char **cmd, t_env *env_lst);
int						ft_echo(char **cmd);
int						ft_env(char **cmd, t_env *env_lst, int i);
int						ft_setenv(char **cmd, t_env **env_lst, int flag);
int						ft_unsetenv(char **cmd, t_env **env_lst);

int						binary_cmd(char **cmd, char **env_array,
						t_env *env_lst); // execution binaire
char					*get_bin_path(char *cmd, t_env *env_lst);
int						check_bin_path(char *bin_path, char *cmd);
int						exec_bin(char *bin_path, char **argv, char **env);

int						dup_std_fd(int *fd);
void					close_and_reset_fd(int *fd);

#endif
