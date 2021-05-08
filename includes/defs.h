#ifndef DEFS_H
# define DEFS_H

# include <termios.h>
# include "libft.h"
# define EOT 4
# define ARROW_UP 'A'
# define ARROW_DOWN 'B'
# define CMD_MAX_LENGTH 4096
# define PWD_PATH_MAX_LENGTH 4096
# define COMMAND_WAIT_TOKEN "$ "
# define REDIRECT_INPUT_TOKEN "<"
# define R_I_T_LEN 1
# define REDIRECT_OUTPUT_TOKEN ">"
# define R_O_T_LEN 1
# define REDIRECT_OUTPUT_APPEND_TOKEN ">>"
# define R_O_A_T_LEN 2
# define SEPARATOR_SEPARATOR_TOKEN ";"
# define S_S_T_LEN 1
# define SEPARATOR_PIPE_TOKEN "|"
# define S_P_T_LEN 1
# define ENV_VARIABLE_PREFIX '$'
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define BACKSLASH '\\'
# define LAST_RETURN_CODE_VAR_NAME '?'
# define NO_BUILTINS 7
# define B_STR "echo cd pwd export unset env exit"

enum e_errors {
	INIT_ERR_TERM_ENV = 1,
	INIT_ERR_TERM_DB,
	INIT_ERR_TERM_UNKNOWN_NAME,
	LEX_ERR_OPEN_SINGLE_QUOTE,
	LEX_ERR_OPEN_DOUBLE_QUOTE,
	LEX_ERR_EOL_AFTER_ESCAPE,
	LEX_ERR_MISSING_REDIRECT_FILE,
	LEX_ERR_EXPECTED_SEPARATOR,
	LEX_ERR_UNKNOWN_COMMAND,
	EXE_ERR_MISSING_AST,
	MALLOC_BREAK
};

enum e_builtins_id {
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
};

enum e_token_types {
	EXECUTABLE,
	ARGUMENT,
	REDIRECT,
	FILE_PATH,
	SEPARATOR
};

typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct s_shell
{
	char			**env;	// environnement variables
	char			pwd_path[PWD_PATH_MAX_LENGTH]; // path to current directory
	char			*pwd; // current directory name
	char			cmd[CMD_MAX_LENGTH]; // command as written by user
	t_list			*tokens; // command after lexer
	t_tree			*ast; // command after parser
	int				status; // status after execution
	int				(*b_fct[NO_BUILTINS])(void *); // builtin functions
	char			**b_str; // builtin functions names
	int				b_strlen[NO_BUILTINS]; // builtin functions names length
	struct termios	*old_settings; // previous terminal settings
	t_list			*cmd_history; // list of previous commands
}				t_shell;

#endif
