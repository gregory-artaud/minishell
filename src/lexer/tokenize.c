#include "minishell.h"

char	*extract_word(char s[CMD_MAX_LENGTH], int *i)
{
	int	start;

	skip_spaces(s, i);
	if (!s[*i] || is_redirect(s, i))
		return (NULL);
	start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && !is_redirect(s, i)
		&& !is_separator(s, i))
		(*i)++;
	if (start == *i)
		return (NULL);
	return (ft_substr(s, start, *i - start));
}

char	*extract_redirect(char s[CMD_MAX_LENGTH], int *i)
{
	if (!ft_memcmp(s + *i, REDIRECT_INPUT_TOKEN, R_I_T_LEN))
	{
		(*i)++;
		return (ft_strdup(REDIRECT_INPUT_TOKEN));
	}
	if (!ft_memcmp(s + *i, REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN))
	{
		*i = *i + 2;
		return (ft_strdup(REDIRECT_OUTPUT_APPEND_TOKEN));
	}
	if (!ft_memcmp(s + *i, REDIRECT_OUTPUT_TOKEN, R_O_T_LEN))
	{
		(*i)++;
		return (ft_strdup(REDIRECT_OUTPUT_TOKEN));
	}
	return (NULL);
}

int	tokenize_args(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	char	*word;
	t_token	*arg;

	skip_spaces(s, i);
	while (s[*i] && !is_redirect(s, i) && !is_separator(s, i))
	{
		word = extract_word(s, i);
		if (!word)
			word = ft_strdup("");
		arg = create_token(ARGUMENT, word);
		if (!arg)
			return (MALLOC_BREAK);
		ft_lstadd_back(&(sh->tokens), ft_lstnew(arg));
		skip_spaces(s, i);
	}
	return (EXIT_SUCCESS);
}

int	tokenize_redirect(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	char	*word;
	t_token	*token;

	skip_spaces(s, i);
	if (!s[*i] || !is_redirect(s, i))
		return (EXIT_SUCCESS);
	word = extract_redirect(s, i);
	if (!word)
		return (MALLOC_BREAK);
	token = create_token(REDIRECT, word);
	if (!token)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(token));
	skip_spaces(s, i);
	if (!s[*i] || is_separator(s, i))
		return (LEX_ERR_MISSING_REDIRECT_FILE);
	word = extract_word(s, i);
	if (!word)
		return (MALLOC_BREAK);
	token = create_token(FILE_PATH, word);
	if (!token)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(token));
	return (EXIT_SUCCESS);
}

int	tokenize_separator(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	char	*word;
	t_token	*token;

	skip_spaces(s, i);
	if (!s[*i])
		return (EXIT_SUCCESS);
	if (!is_separator(s, i))
		return (LEX_ERR_EXPECTED_SEPARATOR);
	word = ft_strndup(s + *i, 1);
	if (!word)
		return (MALLOC_BREAK);
	(*i)++;
	token = create_token(SEPARATOR, word);
	if (!token)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(token));
	return (EXIT_SUCCESS);
}

int	tokenize_cmd(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	char	*word;
	t_token	*exec;
	int		error;

	if (!s[*i])
		return (EXIT_SUCCESS);
	word = extract_word(s, i);
	if (!word)
		return (LEX_ERR_UNKNOWN_COMMAND);
	exec = create_token(EXECUTABLE, word);
	if (!exec)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(exec));
	error = tokenize_args(s, sh, i);
	if (error)
		return (error);
	error = tokenize_redirect(s, sh, i);
	if (error)
		return (error);
	error = tokenize_separator(s, sh, i);
	if (!error)
		return (tokenize_cmd(s, sh, i));
	return (error);
}

int	tokenize(char s[CMD_MAX_LENGTH], t_shell *sh)
{
	int	error;
	int	i;

	if (!*s)
		return (EXIT_SUCCESS);
	i = 0;
	error = tokenize_cmd(s, sh, &i);
	return (error);
}
