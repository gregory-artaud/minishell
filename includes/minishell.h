#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include "libft.h"
# include "defs.h"
# include "execution.h"

int		init_shell(t_shell *sh, char **env);
void	clear_shell(t_shell *sh);
int		set_terminal_settings(t_shell *sh);
void	restore_terminal_settings(t_shell *sh);
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
#endif
