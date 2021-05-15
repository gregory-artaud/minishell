#include "minishell.h"
// FLECHE GAUCHE DROTE MARCHE PAS
void	refresh_input(int i)
{
	int		len;
	char	*s;

	s = (char *)g_sh->current_line->content;
	len = ft_strlen(s);
	move_cursor_left(i);
	clear_line();
	ft_putstr_fd(s, 1);
	move_cursor_left(len - g_sh->i);
}

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
	return (c != 'C' && c != 'D');
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

void	print_history()
{
	t_dlist	*current;

	current = g_sh->cmd_history;
	ft_putchar_fd('\n',1 );
	while (current)
	{
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
}

int	controller(char c)
{
	int	i;
	int	refresh;

	i = g_sh->i;
	refresh = 1;
	if (c == '\t')
		return (0);
	else if (c == 13 || c == '\n')
	{
		ft_strlcpy(g_sh->cmd_history->content, g_sh->current_line->content,
			CMD_MAX_LENGTH);
		return (1);
	}
	else if (c == EOT)
		return (ctrl_d());
	else if (c == 27)
		refresh = termcap(c);
	else if (c == 127)
		del();
	else
		ft_strinsert_fixed(g_sh->current_line->content, CMD_MAX_LENGTH, c,
			(g_sh->i)++);
	if (refresh)
		refresh_input(i);
	return (0);
}
