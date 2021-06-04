#include "minishell.h"

int	get_last_input(char **t, int size)
{
	char	*f;
	int		new_input;
	int		i;

	if (!t)
		return (-1);
	f = NULL;
	i = 0;
	while (i < size)
	{
		if (!ft_memcmp(t[i], REDIRECT_INPUT_TOKEN, R_I_T_LEN + 1))
			f = t[i + 1];
		i += 2;
	}
	if (!f)
		return (-2);
	new_input = open(f, O_RDONLY);
	if (new_input == -1)
		return (-1);
	return (new_input);
}

int	redirect_input(t_tree *tr)
{
	int		old_stdin;
	int		new_input;
	int		tmp;

	new_input = get_last_input(tr->content, tr->size);
	if (new_input == -2)
		return (EXIT_SUCCESS);
	if (new_input == -1)
		return (EXE_ERR_OPEN_FILE);
	old_stdin = dup(STDIN_FILENO);
	if (old_stdin == -1)
		return (EXE_ERR_DUP_FD);
	tmp = dup2(new_input, STDIN_FILENO);
	if (tmp == -1)
	{
		close(new_input);
		close(old_stdin);
		return (EXE_ERR_DUP_FD);
	}
	close(new_input);
	g_sh->old_stdin = old_stdin;
	return (EXIT_SUCCESS);
}

int	get_index(char **t, int size)
{
	int	i;
	int	index;

	index = -1;
	i = 0;
	while (i < size)
	{
		if (!ft_memcmp(t[i], REDIRECT_OUTPUT_TOKEN, R_O_T_LEN + 1)
			|| !ft_memcmp(t[i], REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN + 1))
			index = i;
		i += 2;
	}
	return (index);
}

int	get_last_output(char **t, int size)
{
	int		index;
	int		new_input;
	int		mode;

	if (!t)
		return (-2);
	mode = O_WRONLY;
	index = get_index(t, size);
	if (index == -1)
		return (-2);
	if (!ft_memcmp(t[index], REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN + 1))
		mode |= O_APPEND;
	else
		mode |= O_TRUNC;
	new_input = open(t[index + 1], mode);
	if (new_input == -1)
		return (-1);
	return (new_input);
}

int	redirect_output(t_tree *tr)
{
	int		old_stdout;
	int		new_output;
	int		tmp;

	new_output = get_last_output(tr->content, tr->size);
	if (new_output == -2)
		return (EXIT_SUCCESS);
	if (new_output == -1)
		return (EXE_ERR_OPEN_FILE);
	old_stdout = dup(STDOUT_FILENO);
	if (old_stdout == -1)
		return (EXE_ERR_DUP_FD);
	tmp = dup2(new_output, STDOUT_FILENO);
	if (tmp == -1)
	{
		close(new_output);
		close(old_stdout);
		return (EXE_ERR_DUP_FD);
	}
	close(new_output);
	g_sh->old_stdout = old_stdout;
	return (EXIT_SUCCESS);
}
