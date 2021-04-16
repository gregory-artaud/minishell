#include "minishell.h"

int	executer(t_shell *sh)
{
	if (!sh->ast)
		return (EXE_ERR_MISSING_AST);
	return (EXIT_SUCCESS);
}
