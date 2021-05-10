#include "minishell.h"

void	refresh_input(void)
{
	int		i;
	int		len;
	char	*s;

	s = (char *)g_sh->current_line->content;
	len = ft_strlen(s);
	i = g_sh->i;
	while (--i > 0)
		ft_putchar_fd('\b', 1);
	ft_putstr_fd(s, 1);
	//printf("len:%d;i:%d\n", len, g_sh->i);
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
	//printf(" = %d\n", c);
	if (c == 'h')
		print_history();
	if (c == 13) // carriage return
	{
		ft_strlcpy(g_sh->cmd_history->content, g_sh->current_line->content,
			CMD_MAX_LENGTH);
		return (1);
	}
	if (c == EOT)
		return (ctrl_d());
	if (c == 3)
		return (ctrl_c());
	if (c == 27) // escape
		return (termcap(c));
	if (c == 127)
		return (del());
	ft_strinsert_fixed(g_sh->current_line->content, CMD_MAX_LENGTH, c, g_sh->i);
	((char *)g_sh->current_line->content)[(g_sh->i)++] = c;
	refresh_input();
	return (0);
}
