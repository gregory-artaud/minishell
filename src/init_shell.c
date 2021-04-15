#include "minishell.h"

void	init_shell(t_shell *sh, int argc, char **env)
{
	(void)argc;
	(void)env;
	sh->dir = ft_strdup("$");
}
