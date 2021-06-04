#include "minishell.h"

int	redirect_out_pipe(void)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd == -1)
		return (EXE_ERR_DUP_FD);
	g_sh->old_stdout = fd;
	fd = dup2(g_sh->pright[1], STDOUT_FILENO);
	close(g_sh->pright[1]);
	if (fd == -1)
	{
		close(g_sh->old_stdout);
		return (EXE_ERR_DUP_FD);
	}
	return (EXIT_SUCCESS);
}

int	redirect_in_pipe(void)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (EXE_ERR_DUP_FD);
	g_sh->old_stdin = fd;
	fd = dup2(g_sh->pleft[0], STDIN_FILENO);
	close(g_sh->pleft[0]);
	if (fd == -1)
	{
		close(g_sh->old_stdin);
		return (EXE_ERR_DUP_FD);
	}
	return (EXIT_SUCCESS);
}
