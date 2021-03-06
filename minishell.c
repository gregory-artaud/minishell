#include "minishell.h"

t_shell	*g_sh;

void	prompt(void)
{
	ft_putstr_fd(g_sh->pwd, STDOUT_FILENO);
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
	int		error;

	(void)argc;
	(void)argv;
	g_sh = &sh;
	error = init_shell(&sh, env);
	if (error)
	{
		print_error(error);
		free_shell(&sh);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		clear_shell(&sh);
		if (!run_lexer(&sh))
			if (!run_parser(&sh))
				sh.status = executer(&sh);
	}
	return (EXIT_SUCCESS);
}
