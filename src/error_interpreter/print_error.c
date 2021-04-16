#include "minishell.h"

void	print_error(int error)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (error == LEX_ERR_OPEN_QUOTE)
		ft_putstr_fd("missing single quote.\n", STDERR_FILENO);
	else if (error == LEX_ERR_EOL_AFTER_ESCAPE)
		ft_putstr_fd("missing character after escape.\n", STDERR_FILENO);
	else if (error == EXE_ERR_MISSING_AST)
		ft_putstr_fd("error in syntax tree allocation.\n", STDERR_FILENO);
}
