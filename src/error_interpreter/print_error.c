#include "minishell.h"

void	print_error2(int error)
{
	if (error == INIT_ERR_TERM_ENV)
		ft_putstr_fd("missing \"TERM\" environement variable.\n", STDERR_FILENO);
	else if (error == INIT_ERR_TERM_DB)
		ft_putstr_fd("could not access to the termcap database.\n",
			STDERR_FILENO);
	else if (error == INIT_ERR_TERM_UNKNOWN_NAME)
		ft_putstr_fd("terminal type is not definded in the termcap database.\n",
			STDERR_FILENO);
	else if (error == LEX_ERR_UNKNOWN_SPECIAL_CHAR)
		ft_putstr_fd("unknown special character.\n", STDERR_FILENO);
	else if (error == EXE_ERR_FILE_CREATION)
		ft_putstr_fd("unable to create redirection file.\n", STDERR_FILENO);
	else if (error == EXE_ERR_DUP_FD)
		ft_putstr_fd("unable to duplicate file descriptor.\n", STDERR_FILENO);
	else if (error == EXE_ERR_OPEN_FILE)
		ft_putstr_fd("unable to open file.\n", STDERR_FILENO);
	else if (error == EXE_ERR_FORK)
		ft_putstr_fd("unable to create new process.\n", STDERR_FILENO);
}

void	print_error(int error)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (error == LEX_ERR_OPEN_SINGLE_QUOTE)
		ft_putstr_fd("missing single quote.\n", STDERR_FILENO);
	else if (error == LEX_ERR_OPEN_DOUBLE_QUOTE)
		ft_putstr_fd("missing double quote.\n", STDERR_FILENO);
	else if (error == LEX_ERR_EOL_AFTER_ESCAPE)
		ft_putstr_fd("missing character after escape.\n", STDERR_FILENO);
	else if (error == EXE_ERR_MISSING_AST)
		ft_putstr_fd("error in syntax tree allocation.\n", STDERR_FILENO);
	else if (error == MALLOC_BREAK)
		ft_putstr_fd("error in memory allocation.\n", STDERR_FILENO);
	else if (error == LEX_ERR_MISSING_REDIRECT_FILE)
		ft_putstr_fd("missing redirect file.\n", STDERR_FILENO);
	else if (error == LEX_ERR_UNKNOWN_COMMAND)
		ft_putstr_fd("unknown command.\n", STDERR_FILENO);
	else
		print_error2(error);
}
