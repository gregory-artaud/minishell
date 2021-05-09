#include "minishell.h"

void	refresh_input(void)
{
	int	i;
	int	len;

	len = ft_strlen(g_sh->cmd);
	i = g_sh->i;
	while (--i > 0)
		ft_putchar_fd('\b', 1);
	ft_putstr_fd(g_sh->cmd, 1);
	//printf("len:%d;i:%d\n", len, g_sh->i);
	move_cursor_left(len - g_sh->i);
}

/*
** TO-DO HERE:
**		- command historic with arrow keys up/down
*/
int	termcap(char c)
{
	(void)ft_getchar();
	c = ft_getchar();
	if (c == 'A')
		term_up();
	else if (c == 'B')
		term_down();
	else if (c == 'C')
		term_right();
	else if (c == 'D')
		term_left();
	return (0);
}

int	del(void)
{
	int	i;
	int	len;

	len = ft_strlen(g_sh->cmd);
	i = g_sh->i - 1;
	if (i < 0)
		return (0);
	i--;
	while (++i < len)
		g_sh->cmd[i] = g_sh->cmd[i + 1];
	move_cursor_left(1);
	(g_sh->i)--;
	ft_putstr_fd(g_sh->cmd + g_sh->i, 1);
	ft_putchar_fd(' ', 1);
	move_cursor_left(len - g_sh->i);
	return (0);
}

void	ft_strinsert_fixed(char *s, int size, char c, int index)
{
	if (!s || size < 1 || index >= size || index < 0)
		return ;
	while (--size > index)
		s[size] = s[size - 1];
	s[index] = c;
	return ;
}


int	controller(char c)
{
	//printf(" = %d\n", c);
	if (c == 'e')
		exit(0);
	if (c == 13) // carriage return
		return (1);
	if (c == EOT)
		return (ctrl_d());
	if (c == 3)
		return (ctrl_c());
	if (c == 27) // escape
		return (termcap(c));
	if (c == 127)
		return (del());
	ft_strinsert_fixed(g_sh->cmd, CMD_MAX_LENGTH, c, g_sh->i);
	g_sh->cmd[(g_sh->i)++] = c;
	refresh_input();
	return (0);
}
