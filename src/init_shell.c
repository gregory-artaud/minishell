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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, new_cmd);
	ft_lstclear(&(sh->tokens), free_token);
	clear_ast(&(sh->ast));
	sh->ast = NULL;
}

void	init_env(t_shell *sh, char **env)
{
	int	i;

	i = 0;
	sh->env = 0;
	while (env[i])
	{
		ft_lstadd_back(&sh->env, ft_lstnew(env[i]));
		i++;
	}
}

void	init_shell(t_shell *sh, char **env)
{
	sh->i = 0;
	sh->status = 0;
	sh->ast = NULL;
	init_env(sh, env);
	sh->tokens = NULL;
	sh->cmd_history = ft_dlstnew(ft_calloc(CMD_MAX_LENGTH, sizeof(char)));
	sh->current_line = sh->cmd_history;
	init_terminal();
	init_builtins(sh);
	if (!getcwd(sh->pwd_path, PWD_PATH_MAX_LENGTH))
		ft_bzero(sh->pwd_path, PWD_PATH_MAX_LENGTH);
	set_current_dir(sh);
}

void	free_shell(t_shell *sh)
{
	ft_lstclear(&(sh->tokens), free_token);
	ft_dlstclear(&(sh->cmd_history), free);
	ft_free_strarray(sh->b_str);
	clear_ast(&(sh->ast));
	free(sh->pwd);
	free(sh->pwd_path);
}
