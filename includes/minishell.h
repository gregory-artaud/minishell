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
** parsing/
*/
void	read_cmd(t_shell *sh);
/*
** execution/
*/
int	exec_cmd(t_shell *sh);

#endif
