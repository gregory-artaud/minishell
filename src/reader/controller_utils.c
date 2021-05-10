#include "minishell.h"

int	del(void)
{
	int		i;
	int		len;
	char	*s;

	s = (char *)g_sh->current_line->content;
	len = ft_strlen(s);
	i = g_sh->i - 1;
	if (i < 0)
		return (0);
	i--;
	while (++i < len)
		s[i] = s[i + 1];
	move_cursor_left(1);
	(g_sh->i)--;
	ft_putstr_fd(s + g_sh->i, 1);
	ft_putchar_fd(' ', 1);
	move_cursor_left(len - g_sh->i);
	return (0);
}
