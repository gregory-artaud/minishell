#include "minishell.h"

void	prompt(t_shell *sh)
{
	ft_putstr_fd(sh->pwd, STDOUT_FILENO);
	ft_putstr_fd(COMMAND_WAIT_TOKEN, STDOUT_FILENO);
}

int	run_lexer(t_shell *sh)
{
	int	error;

	error = lexer(sh);
	if (error)
		print_error(error);
	return (error);
}

int	run_parser(t_shell *sh)
{
	int	error;

	error = parser(sh);
	if (error)
		print_error(error);
	return (error);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	init_shell(&sh, env);
	while (1)
	{
		clear_shell(&sh);
		prompt(&sh);
		if (!run_lexer(&sh))
			if (!run_parser(&sh))
				sh.status = executer(&sh);
	}
	return (EXIT_SUCCESS);
}
