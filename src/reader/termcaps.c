#include "minishell.h"

void	term_up(void)
{
	printf("up!\n");
}

void	term_down(void)
{
}

void	term_right(void)
{
	int	i;

	i = g_sh->i;
	if (g_sh->cmd[i] == 0)
		return ;
	move_cursor_right(1);
	g_sh->i = i + 1;
}

void	term_left(void)
{
	int	i;

	i = g_sh->i;
	if (i == 0)
		return ;
	move_cursor_left(1);
	g_sh->i = i - 1;
}
