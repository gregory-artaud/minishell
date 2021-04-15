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

void	init_shell(t_shell *sh, int argc, char **env)
{
	(void)argc;
	(void)env;
	if (!getcwd(sh->pwd, PWD_MAX_LENGTH))
		ft_bzero(sh->pwd, PWD_MAX_LENGTH);
	set_current_dir(sh);
}
