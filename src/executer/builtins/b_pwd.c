#include "minishell.h"

int	b_pwd(void *sh, t_tree *root)
{
	t_shell	*shell;

	(void)root;
	shell = sh;
	ft_putendl_fd(shell->pwd_path, STDOUT_FILENO);
	return (0);
}
