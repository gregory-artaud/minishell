#include "minishell.h"

int	old_set_terminal_settings(t_shell *sh)
{
	t_termios	*old;
	t_termios	*new;

	old = malloc(sizeof(t_termios));
	if (!old)
		return (MALLOC_BREAK);
	new = malloc(sizeof(t_termios));
	if (!new)
		return (MALLOC_BREAK);
	tcgetattr(STDIN_FILENO, old);
	tcgetattr(STDIN_FILENO, new);
	sh->old_settings = old;
	new->c_lflag &= ~(ICANON);
	tcsetattr( STDIN_FILENO, TCSANOW, new);
	sh->new_settings = new;
	return (0);
}

int	set_terminal_settings(t_shell *sh)
{
	static t_termios	old;
	t_termios			new;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	sh->old_settings = &old;
	return (0);
}

void	restore_terminal_settings(t_shell *sh)
{
	tcsetattr( STDIN_FILENO, TCSANOW, sh->old_settings);
}