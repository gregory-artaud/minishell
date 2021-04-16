#include "minishell.h"

void	prompt(t_shell *sh)
{
	ft_putstr_fd(sh->pwd, STDOUT_FILENO);
	ft_putstr_fd(COMMAND_WAIT_TOKEN, STDOUT_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	init_shell(&sh, env);
	while (1)
	{
		prompt(&sh);
		lexer(&sh);
		parser(&sh);
		sh.status = executer(&sh);
	}
	return (EXIT_SUCCESS);
}
