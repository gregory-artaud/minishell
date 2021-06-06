#include "minishell.h"

int	b_exit(void *sh, t_tree *root)
{
	t_shell	*shell;

	(void)root;
	shell = sh;
	free_shell(shell);
	printf("exit\n");
	exit(0);
	return (0);
}
