#include "minishell.h"

void	term_up(void)
{
	int	old;
	int	new;
	int	diff;
	int	i;

	if (!g_sh->current_line->next)
		return ;
	old = ft_strlen(g_sh->current_line->content);
	move_cursor_left(old);
	g_sh->current_line = g_sh->current_line->next;
	new = ft_strlen(g_sh->current_line->content);
	ft_putstr_fd(g_sh->current_line->content, 1);
	diff = old - new + 1;
	i = diff;
	while (--i > 0)
		ft_putchar_fd(' ', 1);
	move_cursor_left(diff - 1);
	g_sh->i = new;
}

void	term_down(void)
{
	int	old;
	int	new;
	int	i;
	int	diff;

	if (!g_sh->current_line->previous)
		return ;
	old = ft_strlen(g_sh->current_line->content);
	move_cursor_left(old);
	g_sh->current_line = g_sh->current_line->previous;
	new = ft_strlen(g_sh->current_line->content);
	ft_putstr_fd(g_sh->current_line->content, 1);
	diff = old - new + 1;
	i = diff;
	while (--i > 0)
		ft_putchar_fd(' ', 1);
	move_cursor_left(diff - 1);
	g_sh->i = new;
}

void	term_right(void)
{
	int	len;
	int	i;

	len = ft_strlen((char *)g_sh->current_line->content);
	i = g_sh->i;
	if (i >= len)
		return ;
	move_cursor_right(1);
	g_sh->i = i + 1;
}

void	term_left(void)
{
	int	i;

	i = g_sh->i;
	if (i <= 0)
		return ;
	move_cursor_left(1);
	g_sh->i = i - 1;
}
