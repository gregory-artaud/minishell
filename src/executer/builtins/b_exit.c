#include "minishell.h"

int	b_exit(void *sh, t_tree *root)
{
	t_shell	*shell;

	(void)root;
	shell = sh;
	clear_ast(&shell->ast);
	exit(0);
	return (0);
}
