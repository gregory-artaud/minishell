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
void	lexer(t_shell *sh);
void	process_line(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j);
void	no_env_var_name(char tmp[CMD_MAX_LENGTH], int *j);
/*
** parser/
*/
void	parser(t_shell *sh);
/*
** execution/
*/
int	executer(t_shell *sh);

#endif
