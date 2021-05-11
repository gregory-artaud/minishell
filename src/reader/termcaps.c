#include "minishell.h"

void	term_up(void)
{
	if (!g_sh->current_line->next)
		return ;
	g_sh->current_line = g_sh->current_line->next;
	g_sh->i = ft_strlen(g_sh->current_line->content);
}

void	term_down(void)
{
	if (!g_sh->current_line->previous)
		return ;
	g_sh->current_line = g_sh->current_line->previous;
	g_sh->i = ft_strlen(g_sh->current_line->content);
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
