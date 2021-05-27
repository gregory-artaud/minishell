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

t_tree	*get_tr_redirect(t_tree *tr)
{
	t_tree	*tmp;

	tmp = ft_tr_leftchild(tr);
	if (!tmp)
		return (NULL);
	if (tmp->type == REDIRECT)
		return (tmp);
	tmp = ft_tr_next_sibling(tmp);
	if (!tmp)
		return (NULL);
	if (tmp->type == REDIRECT)
		return (tmp);
	return (NULL);
}

int	get_last_output(char **t, int size)
{
	int		index;
	int		new_input;
	int		mode;
	int		i;

	if (!t)
		return (-2);
	i = 0;
	index = -1;
	mode = O_WRONLY;
	while (i < size)
	{
		if (!ft_memcmp(t[i], REDIRECT_OUTPUT_TOKEN, R_O_T_LEN + 1) ||
			!ft_memcmp(t[i], REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN + 1))
			index = i;
		i += 2;
	}
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

int	process_redirect(t_tree *tr)
{
	int		error;
	t_tree	*red;

	red = get_tr_redirect(tr);
	if (!red)
		return (EXIT_SUCCESS);
	error = create_files(red);
	if (error)
		return (error);
	error = redirect_input(red);
	if (error)
		return (error);
	error = redirect_output(red);
	if (error)
		return (error);
	return (EXIT_SUCCESS);
}

int	restore_std(void)
{
	int	err;

	if (g_sh->old_stdin != -1)
	{
		err = dup2(g_sh->old_stdin, STDIN_FILENO);
		if (err == -1)
			return (EXE_ERR_DUP_FD);
		close(g_sh->old_stdin);
		g_sh->old_stdin = -1;
	}
	if (g_sh->old_stdout != -1)
	{
		err = dup2(g_sh->old_stdout, STDOUT_FILENO);
		if (err == -1)
			return (EXE_ERR_DUP_FD);
		close(g_sh->old_stdout);
		g_sh->old_stdout = -1;
	}
	return (EXIT_SUCCESS);
	
}

int	execute_command(t_tree *tr)
{
	int		i;
	char	*exec;
	int		error;
	int		status;

	printf("test\n");
	if (tr->type != EXECUTABLE)
		return (EXIT_FAILURE);
	exec = (char *)tr->content;
	if (!ft_strlen(exec))
		return (create_files(ft_tr_leftchild(tr)));
	error = process_redirect(tr);
	if (error)
		return (error);
	i = 0;
	while (i < NO_BUILTINS && ft_memcmp(exec, g_sh->b_str[i], g_sh->b_strlen[i] + 1))
		i++;
	if (i < NO_BUILTINS)
		status = g_sh->b_fct[i](g_sh, tr);
	else
		status = exec_file(tr);
	error = restore_std();
	if (error)
		return (error);
	return (status);
}
