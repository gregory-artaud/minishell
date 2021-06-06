#include "minishell.h"

int	init_builtins(t_shell *sh)
{
	int	i;

	sh->b_str = ft_split(B_STR, ' ');
	if (!sh->b_str)
		return (MALLOC_BREAK);
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
	return (EXIT_SUCCESS);
}

void	clear_shell(t_shell *sh)
{
	reset_signals();
	ft_lstclear(&(sh->tokens), free_token);
	clear_ast(&(sh->ast));
}

void	init_env(t_shell *sh, char **env)
{
	int	i;

	i = 0;
	sh->env = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5))
			ft_lstadd_back(&(sh->env), ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	ft_lstadd_back(&(sh->env), ft_lstnew(ft_strdup(PATH)));
}

int	init_shell(t_shell *sh, char **env)
{
	sh->has_pleft = 0;
	sh->has_pright = 0;
	sh->old_stdin = -1;
	sh->old_stdout = -1;
	sh->i = 0;
	sh->status = 0;
	sh->ast = NULL;
	init_env(sh, env);
	sh->tokens = NULL;
	sh->cmd_history = ft_dlstnew(ft_calloc(CMD_MAX_LENGTH, sizeof(char)));
	if (!sh->cmd_history)
		return (MALLOC_BREAK);
	sh->pwd_path = ft_calloc(PWD_PATH_MAX_LENGTH, sizeof(char));
	if (!sh->pwd_path)
		return (MALLOC_BREAK);
	sh->current_line = sh->cmd_history;
	init_terminal();
	init_builtins(sh);
	if (!getcwd(sh->pwd_path, PWD_PATH_MAX_LENGTH))
		sh->pwd_path = ft_strdup("/");
	set_current_dir(sh);
	return (EXIT_SUCCESS);
}

void	free_shell(t_shell *sh)
{
	ft_lstclear(&(sh->tokens), free_token);
	ft_lstclear(&(sh->env), free);
	ft_dlstclear(&(sh->cmd_history), free);
	ft_free_strarray(sh->b_str);
	clear_ast(&(sh->ast));
	if (sh->pwd)
		free(sh->pwd);
	if (sh->pwd_path)
		free(sh->pwd_path);
}
