#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "defs.h"
# include "execution.h"

extern t_shell	*g_sh;

/*
** TO REMOVE
*/
void	generate_dot(t_tree *tr);

void	init_shell(t_shell *sh, char **env);
void	set_current_dir(t_shell *sh);
void	clear_shell(t_shell *sh);
void	free_shell(t_shell *sh);
void	set_terminal_settings(void);
void	restore_terminal_settings(void);
int		init_terminal(void);
void	push_to_history(t_shell *sh);
void	prompt(void);
/*
** reader
*/
void	read_line(t_shell *sh);
int		termcap(char c);
int		controller(char c);
void	term_up(void);
void	term_down(void);
void	term_right(void);
void	term_left(void);
void	move_cursor_right(int i);
void	move_cursor_left(int i);
int		del(void);
void	del_screen_left(int i);
void	del_screen_right(int i);
void	clear_line(void);
void	delete_l(void);
void	cursor_to_begin(void);
/*
** lexer
*/
int		lexer(t_shell *sh);
int		no_env_var_name(char tmp[CMD_MAX_LENGTH], int *j);
int		is_special(char c);
int		tokenize(t_shell *sh);
int		tokenize_redirect(char s[CMD_MAX_LENGTH], t_shell *sh, int *i);
void	skip_spaces(char s[CMD_MAX_LENGTH], int *i);
t_token	*create_token(int type, char *value);
int		is_redirect(char s[CMD_MAX_LENGTH], int *i);
int		is_separator(char s[CMD_MAX_LENGTH], int *i);
void	free_token(void *t);
int		get_word(char s[CMD_MAX_LENGTH], int *i, char **res);
char	*ft_lstgetenv(char *name);
int		process_single_quote(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j);
int		process_double_quote(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j);
int		process_backslash(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j);
int		process_env(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j);
/*
** parser/
*/
int		parser(t_shell *sh);
char	*my_strdup(char *src, int n);
void	ft_errorzsh(char *cmd);
int		fill_cmd(t_tree *tree, t_list **tk);
void	clear_ast(t_tree **tree);
void	ft_fill_sep(t_shell sh, t_tree *tree);
int		ft_nb_arg(t_list *tk);
void	fill_new_branche(t_token *token, t_tree **tree);
int		ft_nb_redirect(t_list *tk);
int		fill_arg(t_tree *tree, t_list *tk);
int		find_sep(char *str, char sep);
/*
** execution/
*/
int		executer(t_shell *sh);
int		ft_strncmpsep(char *s1, char *s2, unsigned int n, char sep);
int		ft_strlen_sep(char *str, char sep);
void	display_export(t_list *env, int fd);
int		create_file_redirect(t_tree *root);
char	**list_to_char(t_list *env);
int		create_files(t_tree *tr);
int		execute_command(t_tree *tr);
int		exec_file(t_tree *tr);
char	*free_not_env(char *var);
char	*free_env_join(char *dst, char *str);
char	*free_env_join_sep(char *str);
void	exit_not_a_file_error(int type, char *f);
void	execute_path(char *exe, char **argv);
int		get_file_type(char *f);
char	*build_path(char *path, char *exe);
char	**fill_argv(t_tree *tr);
int		redirect_output(t_tree *tr);
int		get_last_output(char **t, int size);
t_tree	*get_tr_redirect(t_tree *tr);
int		redirect_input(t_tree *tr);
int		get_last_input(char **t, int size);
/*
** error_interpreter/
*/
void	print_error(int error);
/*
** signal
*/
int		ctrl_d(void);
int		ctrl_c(void);
void	new_cmd(int i);

#endif
