#include "minishell.h"

void	prompt(t_shell *sh)
{
	ft_putstr_fd(sh->current_dir, STDOUT_FILENO);
	ft_putstr_fd(COMMAND_WAIT_TOKEN, STDOUT_FILENO);
}

int	main(int argc, char **env)
{
	t_shell	sh;

	init_shell(&sh, argc, env);
	while (1)
	{
		prompt(&sh);
		read_cmd(&sh);
		exec_cmd(&sh);
	}
	return (EXIT_SUCCESS);
}
