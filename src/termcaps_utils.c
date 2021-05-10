#include "minishell.h"

void	move_cursor_right(int i)
{
	while (i-- > 0)
		ft_putstr_fd("\033[1C", 1);
}

void	move_cursor_left(int i)
{
	while (i-- > 0)
		ft_putstr_fd("\033[1D", 1);
}
