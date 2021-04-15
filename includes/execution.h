#ifndef EXECUTION_H
# define EXECUTION_H

# include "defs.h"
# include "minishell.h"

/*
** builtins/
*/
int	b_echo(void *sh);
int	b_cd(void *sh);
int	b_pwd(void *sh);
int	b_export(void *sh);
int	b_unset(void *sh);
int	b_env(void *sh);
int	b_exit(void *sh);

#endif
