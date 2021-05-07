#include "minishell.h"

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