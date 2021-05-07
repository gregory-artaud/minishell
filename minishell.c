#include "minishell.h"

void	prompt()
{
	ft_putstr_fd("minishell", STDOUT_FILENO);
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

void	new_cmd(int i)
{
	(void)i;
	write(1, "\n", 1);
	prompt();
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;
	int		error;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, new_cmd);
	error = init_shell(&sh, env);
	if (error)
	{
		print_error(error);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		clear_shell(&sh);
		prompt();
		if (!run_lexer(&sh))
			if (!run_parser(&sh))
				sh.status = executer(&sh);
	}
	return (EXIT_SUCCESS);
}
