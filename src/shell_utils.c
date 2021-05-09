#include "minishell.h"

int	init_terminal(void)
{
	char	*name;
	int		ret;

	name = getenv("TERM");
	if (!name)
		return (INIT_ERR_TERM_ENV);
	ret = tgetent(NULL, name);
	if (ret == -1)
		return (INIT_ERR_TERM_DB);
	if (ret == 0)
		return (INIT_ERR_TERM_UNKNOWN_NAME);
	return (EXIT_SUCCESS);
}

void	set_terminal_settings(void)
{
	struct termios	settings;

	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag &= ~(ICANON);
	settings.c_cc[VMIN] = 1;
	settings.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void	restore_terminal_settings(void)
{
	struct termios	settings;

	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag |= ~(ICANON);
	settings.c_cc[VMIN] = 1;
	settings.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void	push_to_history(t_shell *sh)
{
	char	*cmd;

	cmd = ft_calloc(CMD_MAX_LENGTH, sizeof(char));
	ft_dlstadd_front(&(sh->cmd_history), ft_dlstnew(cmd));
}
