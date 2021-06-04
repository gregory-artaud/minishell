#include "minishell.h"

void	set_current_dir(t_shell *sh)
{
	char	**array;
	int		len;
	int		i;

	array = ft_split(sh->pwd_path, '/');
	len = ft_arrlen(array);
	if (len <= 0)
	{
		free(array);
		sh->pwd = ft_strdup("/");
	}
	else
	{
		sh->pwd = array[len - 1];
		i = -1;
		while (++i < len - 1)
			free(array[i]);
		free(array);
	}
}
