#include "minishell.h"

int	executer(t_shell *sh)
{

	if (!sh->ast)
		return (EXE_ERR_MISSING_AST);
	generate_dot(sh->ast);
	return (EXIT_SUCCESS);
}
