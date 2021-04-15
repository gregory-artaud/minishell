#include "minishell.h"

void	set_current_dir(t_shell *sh)
{
	char 	**array;
	int		len;
	int		i;

	array = ft_split(sh->pwd, '/');
	len = ft_arrlen(array);
	sh->current_dir = array[len - 1];
	i = -1;
	while (++i < len - 1)
		free(array[i]);
	free(array);
}

void	init_builtins(t_shell *sh)
{
	sh->b_str = ft_split(B_STR, ' ');
	sh->b_fct[ECHO] = b_echo;
	sh->b_fct[CD] = b_cd;
	sh->b_fct[PWD] = b_pwd;
	sh->b_fct[EXPORT] = b_export;
	sh->b_fct[UNSET] = b_unset;
	sh->b_fct[ENV] = b_env;
	sh->b_fct[EXIT] = b_exit;
}

void	init_shell(t_shell *sh, char **env)
{
	sh->status = 0;
	sh->ast = NULL;
	sh->env = env;
	if (!getcwd(sh->pwd, PWD_MAX_LENGTH))
		ft_bzero(sh->pwd, PWD_MAX_LENGTH);
	set_current_dir(sh);
}
