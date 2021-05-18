#include "minishell.h"

void	segfault(int i)
{
	printf("Process ended with segmentation fault.\n");
	exit(i);
}

void	set_signals(void)
{
	signal(SIGSEGV, segfault);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	reset_signals(void)
{
	signal(SIGINT, new_cmd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, SIG_DFL);
}
