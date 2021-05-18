#include "minishell.h"

int	change_dir(t_tree *root)
{
	char	**path;

	root = root->branches->content;
	path = root->content;
	if (chdir(path[0]) < 0)
		printf("minishell: %s: %s\n", path[0], strerror(errno));
	return (0);
}

void	verif_redirect(t_tree *root)
{
	t_tree	*tmp;

	tmp = root->branches->content;
	if (tmp->type == REDIRECT)
		create_file_redirect(tmp);
	else if (root->branches->next)
	{
		tmp = root->branches->next->content;
		create_file_redirect(tmp);
		change_dir(root);
	}
	else
		change_dir(root);
}

int	b_cd(void *sh, t_tree *root)
{
	t_shell	*shell;

	shell = sh;
	if (root->branches)
		verif_redirect(root);
	else
		if (chdir(ft_lstgetenv("HOME")) < 0)
			printf("minishell: %s: %s\n", (char *)root->content, strerror(errno));
	if (!getcwd(shell->pwd_path, PWD_PATH_MAX_LENGTH))
		ft_bzero(shell->pwd_path, PWD_PATH_MAX_LENGTH);
	free(shell->pwd);
	shell->pwd = NULL;
	set_current_dir(shell);
	return (0);
}
