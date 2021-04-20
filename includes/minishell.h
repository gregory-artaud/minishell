#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "defs.h"
# include "execution.h"

void	init_shell(t_shell *sh, char **env);
/*
** lexer
*/
int		lexer(t_shell *sh);
int		process_line(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j);
int		no_env_var_name(char tmp[CMD_MAX_LENGTH], int *j);
int		is_special(char c);
int		tokenize(char s[CMD_MAX_LENGTH], t_shell *sh);
/*
** parser/
*/
int		parser(t_shell *sh);
char	*my_strdup(char *src, int n);
int		ft_strlen_sp(char *str, char c);
void	ft_errorzsh(char *cmd);
/*
** execution/
*/
int		executer(t_shell *sh);
/*
** error_interpreter/
*/
void	print_error(int error);
#endif
