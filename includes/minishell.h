#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_shell
{
	char		*dir;
}				t_shell;

void	init_shell(t_shell *sh, int argc, char **env);
/*
** parsing/
*/
void	read_cmd(t_shell *sh);
/*
** execution/
*/
void	exec_cmd(t_shell *sh);

#endif
