#include "minishell.h"

void	move_cursor_right(int i)
{
	char	*tc;
	
	tc = tgetstr("nd", NULL);
	while (i-- > 0)
		tputs (tc, 1, ft_putchar);
}

void	move_cursor_left(int i)
{
	char	*tc;
	
	tc = tgetstr("le", NULL);
	while (--i >= 0)
		tputs(tc, 1, ft_putchar);
}

void	delete_l(void)
{
	char	*tc;

	tc = tgetstr("dl", NULL);
	tputs(tc, 1, ft_putchar);
}

void	cursor_to_begin(void)
{
	char	*tc;
	tc = tgetstr("cr", NULL);
	tputs(tc, 1, ft_putchar);
}
