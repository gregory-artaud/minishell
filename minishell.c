#include "minishell.h"

int	main(int argc, char **env)
{
	t_shell	sh;

	init_shell(&sh, argc, env);
	while (1)
	{
		printf("%s", sh.dir);
		read_cmd(&sh);
		exec_cmd(&sh);
	}
	return (EXIT_SUCCESS);
}
