#include "minishell.h"

int	ft_nb_arg(t_list *tk)
{
	t_token	*token;
	int		nb_arg;

	nb_arg = 0;
	token = tk->content;
	while (tk && token->type != SEPARATOR)
	{
		token = tk->content;
		if (token->type == ARGUMENT)
			nb_arg++;
		tk = tk->next;
	}
	return (nb_arg);
}

int	ft_nb_redirect(t_list *tk)
{
	t_token	*token;
	int		nb_redirect;

	nb_redirect = 0;
	token = tk->content;
	while (tk && token->type != SEPARATOR)
	{
		token = tk->content;
		if (token->type == REDIRECT)
			nb_redirect += 2;
		tk = tk->next;
	}
	return (nb_redirect);
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
