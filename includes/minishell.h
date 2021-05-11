#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/ioctl.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"
# include "defs.h"
# include "execution.h"

extern t_shell	*g_sh;

void	init_shell(t_shell *sh, char **env);
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
void	delete_c(void);
void	delete_l(void);
void	cursor_to_begin(void);
/*
** lexer
*/
int		lexer(t_shell *sh);
int		process_line(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j);
int		no_env_var_name(char tmp[CMD_MAX_LENGTH], int *j);
int		is_special(char c);
int		tokenize(char s[CMD_MAX_LENGTH], t_shell *sh);
void	skip_spaces(char s[CMD_MAX_LENGTH], int *i);
void	goto_space(char s[CMD_MAX_LENGTH], int *i);
t_token	*create_token(int type, char *value);
int		is_redirect(char s[CMD_MAX_LENGTH], int *i);
int		is_separator(char s[CMD_MAX_LENGTH], int *i);
void	free_token(void *t);
/*
** parser/
*/
int		parser(t_shell *sh);
char	*my_strdup(char *src, int n);
void	ft_errorzsh(char *cmd);
int		ft_verif_builtin(char *builtin);
int		fill_cmd(t_shell *sh, t_tree *tree, t_list **tk);
void	clear_ast(t_tree **tree);
void	ft_fill_sep(t_shell sh, t_tree *tree);
int		ft_nb_arg(t_shell sh, t_token *token);
void	fill_new_branche(t_token *token, t_tree **tree);

/*
** execution/
*/
int		executer(t_shell *sh);
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
