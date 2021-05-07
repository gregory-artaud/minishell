#include "minishell.h"

int	ft_nb_arg(t_shell sh, t_token *token)
{
	int	i;

	i = 0;
	while (token->type == ARGUMENT && sh.tokens)
	{
		i++;
		sh.tokens = sh.tokens->next;
		if (sh.tokens)
			token = sh.tokens->content;
	}
	return (i);
}

char	*my_strdup(char *src, int n)
{
	char	*str;

	str = (char *)malloc(sizeof(*str) * n + 1);
	if (str == NULL)
		return (0);
	ft_strncpy(str, src, n);
	return (str);
}

int	my_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				result;

	i = 0;
	while (s1[i] && ((s1[i] == s2[i] || (((unsigned char)s1[i])
					- ((unsigned char)s2[i])) == 32)) && (i < n - 1))
		i++;
	if (s1[i + 1] != 0 || s2[i + 1] != 0)
		return (-1);
	result = ((unsigned char)s1[i]) - ((unsigned char)s2[i]);
	if (result == 32)
		result = 0;
	if (n)
		return (result);
	return (0);
}

void	fill_new_branche(t_token *token, t_tree **tree)
{
	t_tree	*next;

	if ((*tree)->branches == NULL)
	{
		ft_tr_addleft(*tree, ft_tr_new(token->value, token->type, 0));
		*tree = (*tree)->branches->content;
	}
	else
	{
		next = (*tree)->branches->content;
		if (ft_strncmp(next->content, ";", 1) == 0
			|| ft_strncmp(next->content, "|", 1) == 0)
		{
			ft_tr_addleft(*tree, ft_tr_new(token->value, token->type, 0));
			(*tree) = (*tree)->branches->content;
		}
		else
		{
			ft_tr_addright(*tree, ft_tr_new(token->value, token->type, 0));
			(*tree) = (*tree)->branches->next->content;
		}
	}
}

int	ft_verif_builtin(char *builtin)
{
	int		len;

	len = ft_strlen(builtin);
	if (my_strncmp("echo", builtin, len) != 0 && my_strncmp("cd", builtin, len)
		!= 0 && my_strncmp("pwd", builtin, len) != 0
		&& my_strncmp("export", builtin, len) != 0
		&& my_strncmp("unset", builtin, len) != 0
		&& my_strncmp("env", builtin, len) != 0
		&& my_strncmp("exit", builtin, len) != 0)
	{
		if (ft_strncmp(builtin, "./", 2) == 0)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
