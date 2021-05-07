#include "minishell.h"

int	b_exit(void *sh)
{
	t_shell	*shell;

	shell = sh;
	clear_ast(&shell->ast);
	exit(0);
	return (0);
}
