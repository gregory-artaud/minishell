#include "minishell.h"

int	tokenize_redirect_file(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	int		error;
	char	*tmp;
	t_token	*tok;

	skip_spaces(s, i);
	if (!s[*i])
		return (LEX_ERR_MISSING_REDIRECT_FILE);
	tmp = NULL;
	error = get_word(s, i, &tmp);
	if (error)
		return (error);
	if (!tmp)
		return (LEX_ERR_MISSING_REDIRECT_FILE);
	tok = create_token(FILE_PATH, tmp);
	free(tmp);
	if (!tok)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(tok));
	return (EXIT_SUCCESS);
}

char	*get_redirect(char *s, int i)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_memcmp(s + i, REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN))
		tmp = ft_strdup(REDIRECT_OUTPUT_APPEND_TOKEN);
	else if (!ft_memcmp(s + i, REDIRECT_OUTPUT_TOKEN, R_O_T_LEN))
		tmp = ft_strdup(REDIRECT_OUTPUT_TOKEN);
	else if (!ft_memcmp(s + i, REDIRECT_INPUT_TOKEN, R_I_T_LEN))
		tmp = ft_strdup(REDIRECT_INPUT_TOKEN);
	return (tmp);
}

int	tokenize_redirect(char s[CMD_MAX_LENGTH], t_shell *sh, int *i)
{
	int		error;
	char	*tmp;
	t_token	*tok;

	error = 0;
	tmp = NULL;
	skip_spaces(s, i);
	if (!s[*i] || !is_redirect(s, i))
		return (EXIT_SUCCESS);
	tmp = get_redirect(s, *i);
	if (!tmp)
		return (MALLOC_BREAK);
	tok = create_token(REDIRECT, tmp);
	*i += ft_strlen(tmp);
	free(tmp);
	if (!tok)
		return (MALLOC_BREAK);
	ft_lstadd_back(&(sh->tokens), ft_lstnew(tok));
	error = tokenize_redirect_file(s, sh, i);
	if (error)
		return (error);
	return (tokenize_redirect(s, sh, i));
}
