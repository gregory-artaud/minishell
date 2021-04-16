#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "libft.h"
# define CMD_MAX_LENGTH 4096
# define PWD_PATH_MAX_LENGTH 4096
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
	char		pwd_path[PWD_PATH_MAX_LENGTH];
	char		cmd[CMD_MAX_LENGTH];
	char		*pwd;
	char		**env;
	//t_tree		*ast;
	char		**args;
	int			status;
	int			(*b_fct[NO_BUILTINS])(void *);
	char		**b_str;
	int			b_strlen[NO_BUILTINS];
}				t_shell;

#endif
