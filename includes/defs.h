#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "libft.h"
# define CMD_MAX_LENGTH 4096
# define PWD_MAX_LENGTH 4096
# define COMMAND_WAIT_TOKEN "$ "
# define NO_BUILTINS 7
# define B_STR "echo cd pwd export unset env exit"

enum e_builtins_id {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef struct s_shell
{
	char		pwd[PWD_MAX_LENGTH];
	char		cmd[CMD_MAX_LENGTH];
	char		*current_dir;
	char		**env;
	t_tree		*ast;
	int			status;
	int			(*b_fct[NO_BUILTINS])(void *);
	char		**b_str;
}				t_shell;

#endif
