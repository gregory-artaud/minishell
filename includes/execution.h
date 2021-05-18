#ifndef EXECUTION_H
# define EXECUTION_H

# include "defs.h"
# include "minishell.h"

/*
** builtins/
*/
int	b_echo(void *sh, t_tree *root);
int	b_cd(void *sh, t_tree *root);
int	b_pwd(void *sh, t_tree *root);
int	b_export(void *sh, t_tree *root);
int	b_unset(void *sh, t_tree *root);
int	b_env(void *sh, t_tree *root);
int	b_exit(void *sh, t_tree *root);
/*
** exec_signals
*/
void	segfault(int i);
void	set_signals(void);
void	reset_signals(void);

#endif
