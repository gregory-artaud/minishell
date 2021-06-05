#include "minishell.h"

int	tokenize_exec(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	int		error;
	char	*tmp;
	t_token	*tok;

	skip_spaces(s, i);
	error = tokenize_redirect(s, sh, i);
	if (error)
		return (error);
	tmp = NULL;
	error = get_word(s, i, &tmp);
	if (error)
		return (error);
	if (!tmp)
		tmp = ft_strdup("");
	tok = create_token(EXECUTABLE, tmp);
	free(tmp);
	if (!tok)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(tok));
	return (EXIT_SUCCESS);
}

int	tokenize_args(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	char	*arg;
	int		error;
	t_token	*tok;

	error = tokenize_redirect(s, sh, i);
	if (error)
		return (error);
	skip_spaces(s, i);
	arg = NULL;
	error = get_word(s, i, &arg);
	if (error)
		return (error);
	if (!arg)
		return (EXIT_SUCCESS);
	tok = create_token(ARGUMENT, arg);
	free(arg);
	if (!tok)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(tok));
	return (tokenize_args(s, sh, i));
}

int	tokenize_separator(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	int		error;
	char	*sep;
	t_token	*tok;

	error = tokenize_redirect(s, sh, i);
	if (error)
		return (error);
	skip_spaces(s, i);
	if (!s[*i])
		return (EXIT_SUCCESS);
	if (!is_separator(s, i))
		return (LEX_ERR_EXPECTED_SEPARATOR);
	sep = ft_strndup(s + (*i)++, 1);
	if (!sep)
		return (MALLOC_BREAK);
	tok = create_token(SEPARATOR, sep);
	free(sep);
	if (!tok)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(tok));
	return (EXIT_SUCCESS);
}

int	tokenize_cmd(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	int		error;

	skip_spaces(s, i);
	if (!s[*i])
		return (EXIT_SUCCESS);
	error = tokenize_exec(s, sh, i);
	if (error)
		return (error);
	error = tokenize_args(s, sh, i);
	if (error)
		return (error);
	error = tokenize_separator(s, sh, i);
	if (error)
		return (error);
	return (tokenize_cmd(s, sh, i));
}

int	tokenize(t_shell *sh)
{
	int	error;
	int	i;

	if (!*(sh->cmd))
		return (EXIT_SUCCESS);
	i = 0;
	error = tokenize_cmd(sh->cmd, sh, &i);
	return (error);
}
