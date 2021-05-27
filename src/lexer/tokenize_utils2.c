#include "minishell.h"

int	process_special_word(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	int	error;

	error = LEX_ERR_UNKNOWN_SPECIAL_CHAR;
	if (s[*i] == SINGLE_QUOTE)
		error = process_single_quote(s, i, wd, j);
	else if (s[*i] == DOUBLE_QUOTE)
		error = process_double_quote(s, i, wd, j);
	else if (s[*i] == ENV_VARIABLE_PREFIX)
		error = process_env(s, i, wd, j);
	else if (s[*i] == BACKSLASH)
		error = process_backslash(s, i, wd, j);
	return (error);
}

int	process_word(char s[CMD_MAX_LENGTH], int *i, char *res, int *j)
{
	int	error;

	if (!s[*i])
		return (EXIT_SUCCESS);
	error = 0;
	if (is_special(s[*i]))
		error = process_special_word(s, i, res, j);
	else
		res[(*j)++] = s[(*i)++];
	return (error);
}

int	get_word(char s[CMD_MAX_LENGTH], int *i, char **res)
{
	char	*wd;
	int		j;
	int		k;
	int		error;

	skip_spaces(s, i);
	if (!s || !s[*i] || is_separator(s, i))
		return (EXIT_SUCCESS);
	wd = ft_calloc(CMD_MAX_LENGTH, sizeof(char));
	if (!wd)
		return (MALLOC_BREAK);
	j = *i;
	k = 0;
	error = 0;
	while (s[j] && !ft_isspace(s[j]) && !is_separator(s, &j) &&
		!is_redirect(s, &j))
	{
		error = process_word(s, &j, wd, &k);
		if (error)
			break ;
	}
	*i = j;
	*res = wd;
	if (error)
		free(wd);
	return (error);
}

void	free_token(void *t)
{
	t_token	*token;

	token = (t_token *)t;
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}
