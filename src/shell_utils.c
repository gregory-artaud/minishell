#include "minishell.h"

int	init_terminal(void)
{
	char	*name;
	int		ret;

	ret = 1;
	name = getenv("TERM");
	if (!name)
		return (INIT_ERR_TERM_ENV);
	//ret = tgetent(NULL, name);
	if (ret == -1)
		return (INIT_ERR_TERM_DB);
	if (ret == 0)
		return (INIT_ERR_TERM_UNKNOWN_NAME);
	return (EXIT_SUCCESS);
}

void	set_terminal_settings(t_shell *sh)
{
	(void)sh;
	/*
	static struct termios	old;
	struct termios			new;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	sh->old_settings = &old;
	*/
}

void	restore_terminal_settings(t_shell *sh)
{
	tcsetattr(STDIN_FILENO, TCSANOW, sh->old_settings);
}

void	push_to_history(t_shell *sh)
{
	char	*cmd;

	cmd = ft_strdup(sh->cmd);
	ft_lstadd_front(&(sh->cmd_history), ft_lstnew(cmd));
}
