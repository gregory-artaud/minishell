#include "minishell.h"

void	segfault(int i)
{
	printf("Process ended with segmentation fault.\n");
	exit(i);
}

void	send_int(int i)
{
	(void)i;
	kill(g_sh->child_pid, SIGINT);
}

void	send_quit(int i)
{
	(void)i;
	kill(g_sh->child_pid, SIGQUIT);
	if (g_sh->old_stdout != -1)
		ft_putendl_fd("", g_sh->old_stdout);
	else
		ft_putendl_fd("", STDOUT_FILENO);
}

void	set_signals(void)
{
	signal(SIGSEGV, segfault);
	signal(SIGINT, send_int);
	signal(SIGQUIT, send_quit);
}

void	reset_signals(void)
{
	signal(SIGINT, new_cmd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, SIG_DFL);
}
