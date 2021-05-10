#include "minishell.h"

int	b_pwd(void *sh, t_tree *root)
{
	t_shell	*shell;

	(void)root;
	shell = sh;
	printf("%s\n", shell->pwd_path);
	return (0);
}
