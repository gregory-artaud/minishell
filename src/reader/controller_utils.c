#include "minishell.h"

void	del_screen_right(int i)
{
	while (i-- > 0)
		ft_putchar_fd(' ', 1);
	move_cursor_left(i);
}
void	del_screen_left(int i)
{
	move_cursor_left(i);
	del_screen_right(i);
}


int	del(void)
{
	int		i;
	char	*s;

	if (g_sh->i <= 0)
		return (0);
	s = (char *)g_sh->current_line->content;
	(g_sh->i)--;
	i = g_sh->i;
	while (s[i])
	{
		s[i] = s[i + 1];
		i++;
	}
	return (0);
}
