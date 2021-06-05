#include "minishell.h"

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

int	process_redirect(t_tree *tr)
{
	int		error;
	t_tree	*red;

	error = 0;
	red = get_tr_redirect(tr);
	if (red)
	{
		error = create_files(red);
		if (error)
			return (error);
		error = redirect_input(red);
		if (error)
			return (error);
		error = redirect_output(red);
		if (error)
			return (error);
	}
	if (g_sh->has_pleft)
		error = redirect_in_pipe();
	if (g_sh->has_pright)
		error = redirect_out_pipe();
	return (error);
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
	if (g_sh->has_pleft)
		g_sh->has_pleft = 0;
	if (g_sh->has_pright)
		g_sh->has_pright = 0;
	return (EXIT_SUCCESS);
}

int	execute_command(t_tree *tr)
{
	int		i;
	char	*exec;
	int		error;
	int		status;

	if (tr->type != EXECUTABLE)
		return (EXIT_FAILURE);
	exec = (char *)tr->content;
	if (!ft_strlen(exec))
		return (create_files(ft_tr_leftchild(tr)));
	error = process_redirect(tr);
	if (error)
		return (error);
	i = 0;
	while (i < NO_BUILTINS && ft_memcmp(exec, g_sh->b_str[i],
			g_sh->b_strlen[i] + 1))
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
