#include "minishell.h"

int	b_pwd(void *sh)
{
	t_shell	*shell;

	shell = sh;
	printf("%s\n", shell->pwd);
	return (0);
}
