#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

# define CMD_MAX_LENGTH 4096
# define PWD_MAX_LENGTH 4096
# define COMMAND_WAIT_TOKEN "$ "

typedef struct s_shell
{
	char		pwd[PWD_MAX_LENGTH];
	char		cmd[CMD_MAX_LENGTH];
	char		*current_dir;
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
