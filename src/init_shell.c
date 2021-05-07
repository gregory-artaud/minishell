#include "minishell.h"

void	set_current_dir(t_shell *sh)
{
	char 	**array;
	int		len;
	int		i;

	array = ft_split(sh->pwd_path, '/');
	len = ft_arrlen(array);
	sh->pwd = array[len - 1];
	i = -1;
	while (++i < len - 1)
		free(array[i]);
	free(array);
}

void	init_builtins(t_shell *sh)
{
	int	i;

	sh->b_str = ft_split(B_STR, ' ');
	sh->b_fct[B_ECHO] = b_echo;
	sh->b_fct[B_CD] = b_cd;
	sh->b_fct[B_PWD] = b_pwd;
	sh->b_fct[B_EXPORT] = b_export;
	sh->b_fct[B_UNSET] = b_unset;
	sh->b_fct[B_ENV] = b_env;
	sh->b_fct[B_EXIT] = b_exit;
	i = -1;
	while (sh->b_str[++i])
		sh->b_strlen[i] = ft_strlen(sh->b_str[i]);
}

void	clear_shell(t_shell *sh)
{
	ft_lstclear(&(sh->tokens), free_token);
	//free_ast(sh->ast);
}

int		init_shell(t_shell *sh, char **env)
{
	int	error;

	error = 0;
	sh->status = 0;
	sh->ast = NULL;
	sh->env = env;
	sh->tokens = NULL;
	error = set_terminal_settings(sh);
	if (error)
		return (error);
	init_builtins(sh);
	if (!getcwd(sh->pwd_path, PWD_PATH_MAX_LENGTH))
		ft_bzero(sh->pwd_path, PWD_PATH_MAX_LENGTH);
	set_current_dir(sh);
	return (EXIT_SUCCESS);
}

void	free_shell(t_shell *sh)
{
	restore_terminal_settings(sh);
	ft_lstclear(&(sh->tokens), free_token);
	
}
