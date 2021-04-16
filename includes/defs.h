#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "libft.h"
# define CMD_MAX_LENGTH 4096
# define PWD_PATH_MAX_LENGTH 4096
# define COMMAND_WAIT_TOKEN "$ "
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define BACKSLASH '\\'
# define ENV_VARIABLE_TOKEN '$'
# define LAST_RETURN_CODE_VAR_NAME '?'
# define NO_BUILTINS 7
# define B_STR "echo cd pwd export unset env exit"

enum e_errors {
	LEX_ERR_OPEN_QUOTE = 1,
	LEX_ERR_EOL_AFTER_ESCAPE,
	EXE_ERR_MISSING_AST
};

enum e_builtins_id {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_token_types {
	PROGRAM,
	ARGUMENT,
	REDIRECT,
	SEPARATOR
};

typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct s_shell
{
	char		**env;	// environnement variables
	char		pwd_path[PWD_PATH_MAX_LENGTH]; // path to current directory
	char		*pwd; // current directory name
	char		cmd[CMD_MAX_LENGTH]; // command as written by user
	t_list		*tokens; // command after lexer
	t_tree		*ast; // command after parser
	int			status; // status after execution
	int			(*b_fct[NO_BUILTINS])(void *); // builtin functions
	char		**b_str; // builtin functions names
	int			b_strlen[NO_BUILTINS]; // builtin functions names length
}				t_shell;

#endif
